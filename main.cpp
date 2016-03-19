#include <iostream>

#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"

#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/TargetOptions.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Basic/FileManager.h"
#include "clang/Basic/SourceManager.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/Basic/Diagnostic.h"
#include "clang/AST/ASTContext.h"
#include "clang/AST/ASTConsumer.h"
#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Lex/HeaderSearch.h"
#include "clang/Frontend/Utils.h"

/******************************************************************************
 *
 *****************************************************************************/
class MyASTConsumer : public clang::ASTConsumer
{
public:
	MyASTConsumer() : clang::ASTConsumer() { }
	virtual ~MyASTConsumer() { }

	virtual bool HandleTopLevelDecl(clang::DeclGroupRef declarations)
	{
		for(clang::Decl *item : declarations)
		{
			clang::FunctionDecl *vd = llvm::dyn_cast<clang::FunctionDecl>(item);

			if(!vd)
			{
				continue;
			}

			if (vd->hasAttr<clang::VisibilityAttr>())
			{
				std::cout << vd->getDeclName().getAsString();
				std::cout << " returns ";
				std::cout << vd->getReturnType().getAsString();

				std::cout << " (";

				for(uint i = 0; i < vd->getNumParams(); i++)
				{
					clang::ParmVarDecl *param = vd->getParamDecl(i);
					std::cout << param->getDeclName().getAsString();
					std::cout << ", ";
				}
				std::cout << ")";

				std::cout << std::endl;
			}
		}
		return true;
	}
};

/******************************************************************************
 *
 *****************************************************************************/
int main()
{
	using clang::CompilerInstance;
	using clang::TargetOptions;
	using clang::TargetInfo;
	using clang::FileEntry;
	using clang::Token;
	using clang::HeaderSearch;
	using clang::HeaderSearchOptions;
	using clang::ASTContext;
	using clang::ASTConsumer;
	using clang::Parser;
	using clang::DiagnosticOptions;
	using clang::TextDiagnosticPrinter;

	CompilerInstance ci;
	DiagnosticOptions diagnosticOptions;
	ci.createDiagnostics();

	std::shared_ptr<TargetOptions> pto( new TargetOptions());
	pto->Triple = llvm::sys::getDefaultTargetTriple();
	TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), pto);
	ci.setTarget(pti);

	ci.createFileManager();
	ci.createSourceManager(ci.getFileManager());
	ci.createPreprocessor(clang::TranslationUnitKind::TU_Complete);

	MyASTConsumer *astConsumer = new MyASTConsumer();
	ci.setASTConsumer(llvm::make_unique<MyASTConsumer>());

	ci.createASTContext();

	const FileEntry *pFile = ci.getFileManager().getFile("/home/bernardo/projects/c/libsodium/src/libsodium/include/sodium.h");
	ci.getSourceManager().setMainFileID(ci.getSourceManager().createFileID(pFile, clang::SourceLocation(), clang::SrcMgr::C_User));
	ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(),
											 &ci.getPreprocessor());
	clang::ParseAST(ci.getPreprocessor(), astConsumer, ci.getASTContext());
	ci.getDiagnosticClient().EndSourceFile();

	return 0;
}
