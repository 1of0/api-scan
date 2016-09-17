#include "SourceInfoASTConsumer.h"

namespace ApiScan
{
	bool SourceInfoASTConsumer::HandleTopLevelDecl(DeclGroupRef declarations)
	{
		for (Decl *item : declarations)
		{
			FunctionDecl *functionDeclaration = dyn_cast<FunctionDecl>(item);
			RecordDecl *recordDeclaration = dyn_cast<RecordDecl>(item);

			if (functionDeclaration && functionDeclaration->hasAttr<VisibilityAttr>() && !this->ci->getSourceManager().isInSystemHeader(functionDeclaration->getLocStart()))
			{
				this->VisitFunctionDeclaration(functionDeclaration);
			}
			
			if (recordDeclaration && recordDeclaration->isStruct() && !this->ci->getSourceManager().isInSystemHeader(recordDeclaration->getLocStart()))
			{
				this->VisitRecordDeclaration(recordDeclaration);
			}
		}
		return true;
	}

	void SourceInfoASTConsumer::VisitFunctionDeclaration(FunctionDecl *declaration)
	{
		FunctionInfo functionInfo(
			declaration->getDeclName().getAsString(),
			typeTranslator.translate(declaration->getReturnType().getAsString())
		);

		for (const ParmVarDecl *parameterDeclaration : declaration->parameters())
		{
			ParameterInfo parameterInfo(
				paramTranslator.translate(parameterDeclaration->getDeclName().getAsString()),
				typeTranslator.translate(parameterDeclaration->getType().getAsString())
			);

			functionInfo.addParameter(parameterInfo);
		}

		sourceInfo.addFunction(functionInfo);
	}

	void SourceInfoASTConsumer::VisitRecordDeclaration(RecordDecl *declaration)
	{
		StructInfo structInfo(declaration->getDeclName().getAsString());

		for (FieldDecl *fieldDeclaration : declaration->fields())
		{
			FieldInfo fieldInfo(
				paramTranslator.translate(fieldDeclaration->getDeclName().getAsString()),
				typeTranslator.translate(fieldDeclaration->getType().getAsString())
			);

			structInfo.addField(fieldInfo);
		}

		sourceInfo.addStruct(structInfo);
	}
}

