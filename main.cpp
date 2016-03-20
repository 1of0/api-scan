#include <iostream>
#include <sstream>

#include "llvm/Support/Host.h"
#include "llvm/ADT/IntrusiveRefCntPtr.h"

#include "clang/Basic/DiagnosticOptions.h"
#include "clang/Frontend/TextDiagnosticPrinter.h"
#include "clang/Frontend/CompilerInstance.h"
#include "clang/Basic/TargetInfo.h"
#include "clang/Lex/Preprocessor.h"
#include "clang/AST/ASTContext.h"
#include "clang/Parse/Parser.h"
#include "clang/Parse/ParseAST.h"
#include "clang/Lex/HeaderSearch.h"

using std::string;
using std::shared_ptr;
using std::vector;

string exec(const char* cmd);
vector<string> getGccIncludes();

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
	using clang::TranslationUnitKind;

	CompilerInstance ci;
	ci.createDiagnostics();

	std::shared_ptr<TargetOptions> pto(new TargetOptions());
	pto->Triple = llvm::sys::getDefaultTargetTriple();

	TargetInfo *pti = TargetInfo::CreateTargetInfo(ci.getDiagnostics(), pto);
	ci.setTarget(pti);

	ci.createFileManager();
	ci.createSourceManager(ci.getFileManager());

	for (std::string include : getGccIncludes())
	{
		ci.getHeaderSearchOpts().AddPath(include, clang::frontend::Angled, false, false);
	}

	ci.createPreprocessor(TranslationUnitKind::TU_Complete);

	MyASTConsumer *astConsumer = new MyASTConsumer();
	ci.setASTConsumer(llvm::make_unique<MyASTConsumer>());

	ci.createASTContext();

	const FileEntry *pFile = ci.getFileManager().getFile("/home/bernardo/projects/c/libsodium/src/libsodium/include/sodium.h");
	ci.getSourceManager().setMainFileID(ci.getSourceManager().createFileID(pFile, clang::SourceLocation(), clang::SrcMgr::C_User));
	ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), &ci.getPreprocessor());
	clang::ParseAST(ci.getPreprocessor(), astConsumer, ci.getASTContext());
	ci.getDiagnosticClient().EndSourceFile();

	return 0;
}

vector<string> getGccIncludes()
{
	string result = exec("echo | gcc -Wp,-v -x c - -fsyntax-only 2>&1");
	vector<string> includes;

	std::stringstream stream(result);
	string line;
	bool listingIncludes = false;

	while (std::getline(stream, line, '\n'))
	{
		if (line == "#include \\\"...\\\" search starts here:" || line == "#include <...> search starts here:")
		{
			listingIncludes = true;
			continue;
		}

		if (line == "End of search list.")
		{
			listingIncludes = false;
			continue;
		}

		if (listingIncludes)
		{
			includes.push_back(line.substr(1));
		}
	}

	return includes;
}

string exec(const char* cmd)
{
	shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);

	if (!pipe)
	{
		return "";
	}

	char buffer[128];
	string result = "";

	while (!feof(pipe.get()))
	{
		if (fgets(buffer, 128, pipe.get()) != NULL)
		{
			result += buffer;
		}
	}

	return result;
}