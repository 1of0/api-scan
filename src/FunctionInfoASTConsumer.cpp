#include "FunctionInfoASTConsumer.h"

namespace ApiScan
{
	bool FunctionInfoASTConsumer::HandleTopLevelDecl(DeclGroupRef declarations)
	{
		for (Decl *item : declarations)
		{
			FunctionDecl *functionDeclaration = dyn_cast<FunctionDecl>(item);

			if (!functionDeclaration || !functionDeclaration->hasAttr<VisibilityAttr>())
			{
				continue;
			}

			FunctionInfo functionInfo(
				functionDeclaration->getDeclName().getAsString(),
				typeTranslator.translate(functionDeclaration->getReturnType().getAsString())
			);

			for (uint i = 0; i < functionDeclaration->getNumParams(); i++)
			{
				ParmVarDecl *parameterDeclaration = functionDeclaration->getParamDecl(i);

				ParameterInfo parameterInfo(
					paramTranslator.translate(parameterDeclaration->getDeclName().getAsString()),
					typeTranslator.translate(parameterDeclaration->getType().getAsString())
				);

				functionInfo.addParameter(parameterInfo);
			}

			functions.push_back(functionInfo);
		}
		return true;
	}
}

