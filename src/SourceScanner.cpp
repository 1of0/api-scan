#include "SourceScanner.h"

namespace ApiScan
{
	void SourceScanner::scan(const string file)
	{
		this->compiler.createDiagnostics();
		
		this->compiler.getDiagnostics().setClient(new IgnoringDiagConsumer());

		shared_ptr<TargetOptions> targetOptions(new TargetOptions());
		targetOptions->Triple = llvm::sys::getDefaultTargetTriple();

		this->compiler.setTarget(TargetInfo::CreateTargetInfo(this->compiler.getDiagnostics(), targetOptions));

		this->compiler.createFileManager();
		this->compiler.createSourceManager(this->compiler.getFileManager());

		for (string include : getGccIncludes())
		{
			this->compiler.getHeaderSearchOpts().AddPath(include, clang::frontend::System, false, false);
		}

		this->compiler.createPreprocessor(TranslationUnitKind::TU_Complete);
		this->compiler.createASTContext();

		Preprocessor &preprocessor = this->compiler.getPreprocessor();
		//preprocessor.addPPCallbacks(std::unique_ptr<PPCallbacks>(new PreProcessorVisitor(this)));

		clang::FileID fileId = this->compiler.getSourceManager().createFileID(
			this->compiler.getFileManager().getFile(file),
			clang::SourceLocation(),
			clang::SrcMgr::C_User
		);
		this->compiler.getSourceManager().setMainFileID(fileId);
		
		this->compiler.getDiagnosticClient().BeginSourceFile(this->compiler.getLangOpts(), &preprocessor);

		clang::ParseAST(preprocessor, this->visitor, this->compiler.getASTContext());

		this->compiler.getDiagnosticClient().EndSourceFile();

		DoPrintMacros(preprocessor, &llvm::outs());
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




