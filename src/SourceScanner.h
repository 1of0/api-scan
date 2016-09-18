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

#include "DeclarationVisitor.h"
#include "Translator.h"

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
using clang::IgnoringDiagConsumer;
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
	friend class DeclarationVisitor;
	private:
		Translator paramTranslator;
		Translator typeTranslator;
		Translator fieldTranslator;

		CompilerInstance compiler;
		DeclarationVisitor *visitor;
		SourceInfo sourceInfo;

		vector<string> getGccIncludes();

	public:
		SourceScanner()
		{
			this->visitor = new DeclarationVisitor(this);
			this->paramTranslator = NullTranslator();
			this->typeTranslator = NullTranslator();
			this->fieldTranslator = NullTranslator();
		}

		const SourceInfo getSourceInfo() { return this->sourceInfo; }

		void setTypeTranslator(Translator &typeTranslator) { this->typeTranslator = typeTranslator; }
		void setParamTranslator(Translator &paramTranslator) { this->paramTranslator = paramTranslator; }
		void setFieldTranslator(Translator &fieldTranslator) { this->fieldTranslator = fieldTranslator; }

		void scan(const string file);
	};
}