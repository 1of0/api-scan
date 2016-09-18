#include "DeclarationVisitor.h"
#include "SourceScanner.h"

namespace ApiScan
{
	bool DeclarationVisitor::HandleTopLevelDecl(DeclGroupRef declarations)
	{
		for (Decl *item : declarations)
		{
			FunctionDecl *functionDeclaration = dyn_cast<FunctionDecl>(item);
			RecordDecl *recordDeclaration = dyn_cast<RecordDecl>(item);

			if (functionDeclaration && functionDeclaration->hasAttr<VisibilityAttr>() && !this->isInSystemHeader(functionDeclaration->getLocStart()))
			{
				this->VisitFunctionDeclaration(functionDeclaration);
			}
			
			if (recordDeclaration && recordDeclaration->isStruct() && !this->isInSystemHeader(recordDeclaration->getLocStart()))
			{
				this->VisitRecordDeclaration(recordDeclaration);
			}
		}
		return true;
	}

	void DeclarationVisitor::VisitFunctionDeclaration(FunctionDecl *declaration)
	{
		FunctionInfo functionInfo(
			declaration->getDeclName().getAsString(),
			this->translateType(declaration->getReturnType().getAsString())
		);

		for (const ParmVarDecl *parameterDeclaration : declaration->parameters())
		{
			ParameterInfo parameterInfo(
				this->translateParam(parameterDeclaration->getDeclName().getAsString()),
				this->translateType(parameterDeclaration->getType().getAsString())
			);

			functionInfo.addParameter(parameterInfo);
		}

		this->parent->sourceInfo.addFunction(functionInfo);
	}

	void DeclarationVisitor::VisitRecordDeclaration(RecordDecl *declaration)
	{
		StructInfo structInfo(declaration->getDeclName().getAsString());

		for (FieldDecl *fieldDeclaration : declaration->fields())
		{
			FieldInfo fieldInfo(
				fieldDeclaration->getDeclName().getAsString(),
				this->translateType(fieldDeclaration->getType().getAsString())
			);

			structInfo.addField(fieldInfo);
		}

		this->parent->sourceInfo.addStruct(structInfo);
	}

	const string DeclarationVisitor::translateType(const string typeName) { return this->parent->typeTranslator.translate(typeName); }
	const string DeclarationVisitor::translateParam(const string paramName) { return this->parent->paramTranslator.translate(paramName); }
	const string DeclarationVisitor::translateField(const string fieldName) { return this->parent->fieldTranslator.translate(fieldName); }
	bool DeclarationVisitor::isInSystemHeader(const SourceLocation location) { return parent->compiler.getSourceManager().isInSystemHeader(location); }
}

