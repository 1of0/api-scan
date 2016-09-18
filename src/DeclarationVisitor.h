#pragma once

#include <iostream>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Attr.h>
#include <clang/Frontend/CompilerInstance.h>

#include "InfoTypes.h"

using clang::ASTConsumer;
using clang::CompilerInstance;
using clang::Decl;
using clang::DeclGroupRef;
using clang::FieldDecl;
using clang::FunctionDecl;
using clang::ParmVarDecl;
using clang::RecordDecl;
using clang::SourceLocation;
using clang::VisibilityAttr;

using llvm::dyn_cast;

namespace ApiScan
{
	class SourceScanner;

	class DeclarationVisitor : public ASTConsumer
	{
	private:
		SourceScanner *parent;
		
		virtual bool HandleTopLevelDecl(DeclGroupRef declarations) override;

		void VisitFunctionDeclaration(FunctionDecl *declaration);
		void VisitRecordDeclaration(RecordDecl *declaration);

		const string translateType(const string typeName);
		const string translateParam(const string paramName);
		const string translateField(const string fieldName);
		bool isInSystemHeader(const SourceLocation location);

	public:
		DeclarationVisitor(SourceScanner *parent)
		{
			this->parent = parent;
		}
	};
}