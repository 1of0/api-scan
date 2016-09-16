#include "FunctionScanner.h"

namespace ApiScan
{
	vector<FunctionInfo> FunctionScanner::scan(string file)
	{
		CompilerInstance ci;
		ci.createDiagnostics();

		shared_ptr<TargetOptions> targetOptions(new TargetOptions());
		targetOptions->Triple = llvm::sys::getDefaultTargetTriple();

		ci.setTarget(TargetInfo::CreateTargetInfo(ci.getDiagnostics(), targetOptions));

		ci.createFileManager();
		ci.createSourceManager(ci.getFileManager());

		for (string include : getGccIncludes())
		{
			ci.getHeaderSearchOpts().AddPath(include, clang::frontend::Angled, false, false);
		}

		ci.createPreprocessor(TranslationUnitKind::TU_Complete);
		ci.createASTContext();

		clang::FileID fileId = ci.getSourceManager().createFileID(
			ci.getFileManager().getFile(file),
			clang::SourceLocation(),
			clang::SrcMgr::C_User
		);
		ci.getSourceManager().setMainFileID(fileId);

		ci.getDiagnosticClient().BeginSourceFile(ci.getLangOpts(), &ci.getPreprocessor());
		clang::ParseAST(ci.getPreprocessor(), &astConsumer, ci.getASTContext());
		ci.getDiagnosticClient().EndSourceFile();

		return astConsumer.getFunctions();
	}

	vector<string> FunctionScanner::getGccIncludes()
	{
		string result = ApiScan::Util::executeCommand("echo | gcc -Wp,-v -x c - -fsyntax-only 2>&1");
		vector<string> includes;

		stringstream stream(result);
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
}




