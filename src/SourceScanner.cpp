#include "SourceScanner.h"

namespace ApiScan
{
	SourceInfo SourceScanner::scan(string file)
	{
		this->ci.createDiagnostics();

		shared_ptr<TargetOptions> targetOptions(new TargetOptions());
		targetOptions->Triple = llvm::sys::getDefaultTargetTriple();

		this->ci.setTarget(TargetInfo::CreateTargetInfo(this->ci.getDiagnostics(), targetOptions));

		this->ci.createFileManager();
		this->ci.createSourceManager(this->ci.getFileManager());

		for (string include : getGccIncludes())
		{
			this->ci.getHeaderSearchOpts().AddPath(include, clang::frontend::System, false, false);
		}

		this->ci.createPreprocessor(TranslationUnitKind::TU_Complete);
		this->ci.createASTContext();

		clang::FileID fileId = this->ci.getSourceManager().createFileID(
			this->ci.getFileManager().getFile(file),
			clang::SourceLocation(),
			clang::SrcMgr::C_User
		);
		this->ci.getSourceManager().setMainFileID(fileId);

		this->ci.getDiagnosticClient().BeginSourceFile(this->ci.getLangOpts(), &this->ci.getPreprocessor());

		clang::ParseAST(this->ci.getPreprocessor(), &astConsumer, this->ci.getASTContext());

		this->ci.getDiagnosticClient().EndSourceFile();

		return astConsumer.getSourceInfo();
	}

	vector<string> SourceScanner::getGccIncludes()
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




