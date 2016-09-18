#pragma once

#include <sstream>
#include <string>
#include <vector>
#include <memory>

#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Parse/Parser.h>

#include "SourceInfoASTConsumer.h"

using std::shared_ptr;
using std::string;
using std::stringstream;
using std::vector;

using clang::ASTConsumer;
using clang::ASTContext;
using clang::CompilerInstance;
using clang::DiagnosticOptions;
using clang::FileEntry;
using clang::HeaderSearch;
using clang::HeaderSearchOptions;
using clang::Parser;
using clang::TargetInfo;
using clang::TargetOptions;
using clang::TextDiagnosticPrinter;
using clang::Token;
using clang::TranslationUnitKind;

namespace ApiScan
{
	class SourceScanner
	{
	private:
		CompilerInstance ci;

		SourceInfoASTConsumer astConsumer;

		vector<string> getGccIncludes();

	public:
		SourceScanner()
		{
			astConsumer.setCompilerInstance(&ci);
		}

		void setParamTranslator(Translator &paramTranslator) { this->astConsumer.setParamTranslator(paramTranslator); }
		void setTypeTranslator(Translator &typeTranslator) { this->astConsumer.setTypeTranslator(typeTranslator); }

		SourceInfo scan(string file);
	};
}