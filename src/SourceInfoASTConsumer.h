#pragma once

#include <iostream>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Attr.h>
#include <clang/Frontend/CompilerInstance.h>

#include "InfoTypes.h"
#include "Translator.h"

using clang::ASTConsumer;
using clang::CompilerInstance;
using clang::Decl;
using clang::DeclGroupRef;
using clang::FieldDecl;
using clang::FunctionDecl;
using clang::ParmVarDecl;
using clang::RecordDecl;
using clang::VisibilityAttr;

using llvm::dyn_cast;

namespace ApiScan
{
	class SourceInfoASTConsumer;

	class SourceInfoASTConsumer: public ASTConsumer
	{
	private:
		Translator paramTranslator;
		Translator typeTranslator;
		CompilerInstance *ci;

		SourceInfo sourceInfo;

		virtual bool HandleTopLevelDecl(DeclGroupRef declarations) override;

		void VisitFunctionDeclaration(FunctionDecl *declaration);
		void VisitRecordDeclaration(RecordDecl *declaration);

	public:

		SourceInfoASTConsumer()
		{
			paramTranslator = NullTranslator();
			typeTranslator = NullTranslator();
		}

		void setParamTranslator(Translator &paramTranslator) { this->paramTranslator = paramTranslator; }
		void setTypeTranslator(Translator &typeTranslator) { this->typeTranslator = typeTranslator; }
		void setCompilerInstance(CompilerInstance *ci) { this->ci = ci; }

		const SourceInfo &getSourceInfo() const { return this->sourceInfo; }
	};

}