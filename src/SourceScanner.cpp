#include "SourceScanner.hpp"

namespace ApiScan
{
	void SourceScanner::scan(const string file)
	{
		compiler.createDiagnostics();

		compiler.getDiagnostics().setClient(new clang::IgnoringDiagConsumer());

		shared_ptr<clang::TargetOptions> targetOptions(new clang::TargetOptions());
		targetOptions->Triple = llvm::sys::getDefaultTargetTriple();

		compiler.setTarget(clang::TargetInfo::CreateTargetInfo(compiler.getDiagnostics(), targetOptions));

		compiler.createFileManager();
		compiler.createSourceManager(compiler.getFileManager());

		for (string include : ApiScan::Util::getGccIncludes())
		{
			compiler.getHeaderSearchOpts().AddPath(include, clang::frontend::System, false, false);
		}

		compiler.createPreprocessor(clang::TranslationUnitKind::TU_Complete);
		compiler.createASTContext();

		scanDeclarations(file);
		scanMacros();
	}

	void SourceScanner::scanDeclarations(const string file)
	{
		clang::FileID fileId = compiler.getSourceManager().createFileID(
			compiler.getFileManager().getFile(file),
			clang::SourceLocation(),
			clang::SrcMgr::C_User
		);
		compiler.getSourceManager().setMainFileID(fileId);

		compiler.getDiagnosticClient().BeginSourceFile(compiler.getLangOpts(), &compiler.getPreprocessor());

		clang::ParseAST(compiler.getPreprocessor(), this, compiler.getASTContext());

		compiler.getDiagnosticClient().EndSourceFile();
	}

	void SourceScanner::scanMacros()
	{
		NamedMacroMap macroIndex = findDefines();

		for (NamedMacroMap::value_type pair : macroIndex)
		{
			clang::MacroInfo *macroInfo = pair.second;

			if (macroInfo->isFunctionLike() || !isLocationInScope(macroInfo->getDefinitionLoc()))
			{
				continue;
			}

			DefineInfo defineInfo;
			defineInfo.name = pair.first;
			defineInfo.expansion = getMacroValue(macroInfo, macroIndex);

			sourceMap.addDefine(defineInfo);
		}
	}

	NamedMacroMap SourceScanner::findDefines()
	{
		NamedMacroMap macroIndex;

		for (const auto &macro : compiler.getPreprocessor().macros())
		{
			if (!macro.second.getLatest())
			{
				continue;
			}

			clang::MacroInfo *macroInfo = macro.second.getLatest()->getMacroInfo();

			if (!macroInfo->isUsedForHeaderGuard())
			{
				macroIndex[macro.first->getName().str()] = macroInfo;
			}
		}

		return macroIndex;
	}

	string SourceScanner::getMacroValue(clang::MacroInfo *macroInfo, NamedMacroMap &macroIndex)
	{
		string buffer;

		for (const clang::Token &token : macroInfo->tokens())
		{
			if (token.hasLeadingSpace())
			{
				buffer += " ";
			}
			buffer += getTokenValue(token, macroIndex);
		}

		return buffer;
	}

	string SourceScanner::getTokenValue(const clang::Token &token, NamedMacroMap &macroIndex)
	{
		string tokenValue = compiler.getPreprocessor().getSpelling(token);

		if (token.isLiteral() || macroIndex.count(tokenValue) == 0)
		{
			return translator.translate(DictType, tokenValue);
		}

		// Expand tokens that refer to another known macro definition
		return getMacroValue(macroIndex[tokenValue], macroIndex);
	}

	bool SourceScanner::HandleTopLevelDecl(clang::DeclGroupRef declarations)
	{
		for (clang::Decl *item : declarations)
		{
			clang::FunctionDecl *functionDeclaration = clang::dyn_cast<clang::FunctionDecl>(item);
			clang::RecordDecl *recordDeclaration = clang::dyn_cast<clang::RecordDecl>(item);
			clang::TypedefNameDecl *typedefDeclaration = clang::dyn_cast<clang::TypedefNameDecl>(item);

			if (functionDeclaration && functionDeclaration->hasAttr<clang::VisibilityAttr>() && isLocationInScope(functionDeclaration->getLocStart()))
			{
				handleFunctionDeclaration(functionDeclaration);
			}

			if (recordDeclaration && recordDeclaration->isStruct() && isLocationInScope(recordDeclaration->getLocStart()))
			{
				handleRecordDeclaration(recordDeclaration);
			}

			if (typedefDeclaration && isLocationInScope(typedefDeclaration->getLocStart()))
			{
				handleTypedefDeclaration(typedefDeclaration);
			}
		}
		return true;
	}

	void SourceScanner::handleFunctionDeclaration(clang::FunctionDecl *declaration)
	{
		FunctionInfo functionInfo = {};
		functionInfo.name = declaration->getDeclName().getAsString();
		functionInfo.returnType = getTypeInfo(declaration->getReturnType());

		for (const clang::ParmVarDecl *parameterDeclaration : declaration->parameters())
		{
			ParameterInfo parameterInfo = {};
			parameterInfo.name = translator.translate(DictParam, parameterDeclaration->getDeclName().getAsString());
			parameterInfo.type = getTypeInfo(parameterDeclaration->getType());

			if (parameterDeclaration->hasAttr<clang::AlignedAttr>())
			{
				parameterInfo.alignment = parameterDeclaration->getAttr<clang::AlignedAttr>()->getAlignment(compiler.getASTContext()) / 8;
			}

			functionInfo.parameters.push_back(parameterInfo);
		}

		sourceMap.addFunction(functionInfo);
	}

	void SourceScanner::handleRecordDeclaration(clang::RecordDecl *declaration)
	{
		StructInfo structInfo = {};
		structInfo.name = declaration->getDeclName().getAsString();

		for (const clang::FieldDecl *fieldDeclaration : declaration->fields())
		{
			FieldInfo fieldInfo = {};
			fieldInfo.name = translator.translate(DictField, fieldDeclaration->getDeclName().getAsString());
			fieldInfo.type = getTypeInfo(fieldDeclaration->getType());

			if (fieldDeclaration->hasAttr<clang::AlignedAttr>())
			{
				fieldInfo.alignment = fieldDeclaration->getAttr<clang::AlignedAttr>()->getAlignment(compiler.getASTContext()) / 8;
			}

			structInfo.fields.push_back(fieldInfo);
		}

		const clang::ASTRecordLayout &structLayout = compiler.getASTContext().getASTRecordLayout(declaration);

		if (structLayout.getFieldCount() == structInfo.fields.size())
		{
			for (unsigned int i = 0; i < structInfo.fields.size(); i++)
			{
				structInfo.fields[i].offsetDefined = true;
				structInfo.fields[i].offset = structLayout.getFieldOffset(i) / 8;
			}
		}

		sourceMap.addStruct(structInfo);
	}

	void SourceScanner::handleTypedefDeclaration(clang::TypedefNameDecl *declaration)
	{
		declaration = declaration->getCanonicalDecl();

		TypedefInfo typedefInfo = {};
		typedefInfo.name = declaration->getDeclName().getAsString();
		typedefInfo.type = getTypeInfo(declaration->getUnderlyingType());

		if (declaration->hasAttr<clang::AlignedAttr>())
		{
			typedefInfo.alignment = declaration->getAttr<clang::AlignedAttr>()->getAlignment(compiler.getASTContext()) / 8;
		}

		sourceMap.addTypedef(typedefInfo);
	}

	TypeInfo SourceScanner::getTypeInfo(const clang::QualType &type)
	{
		TypeInfo typeInfo = {};
		typeInfo.name = translator.translate(DictType, type.getDesugaredType(compiler.getASTContext()).getAsString());

		if (type->getAs<clang::DecayedType>())
		{
			const clang::ConstantArrayType *arrayInfo = clang::dyn_cast<clang::ConstantArrayType>(type->getAs<clang::DecayedType>()->getOriginalType());

			if (arrayInfo)
			{
				typeInfo.constantArraySize = arrayInfo->getSize().getZExtValue();
			}
		}

		return typeInfo;
	}

	bool SourceScanner::isLocationInScope(const clang::SourceLocation location)
	{
		return !compiler.getSourceManager().isInSystemHeader(location);
	}
}
