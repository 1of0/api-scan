#pragma once

#include <string>
#include <vector>
#include <map>

#include <clang/Basic/TargetInfo.h>
#include <clang/Frontend/CompilerInstance.h>
#include <clang/Frontend/TextDiagnosticPrinter.h>
#include <clang/Parse/ParseAST.h>
#include <clang/Parse/Parser.h>
#include <llvm/ADT/SmallString.h>

#include "InfoTypes.hpp"
#include "Translator.hpp"
#include "Util.hpp"

using std::shared_ptr;
using std::string;
using std::stringstream;
using std::vector;
using std::map;

namespace ApiScan
{
	typedef map<string, clang::MacroInfo *> NamedMacroMap;

	class SourceScanner : public clang::ASTConsumer
	{
	private:
		clang::CompilerInstance compiler;

		SourceMap sourceMap;
		Translator translator;

		void scanDeclarations(const string file);
		void scanMacros();

		NamedMacroMap findDefines();
		string getMacroValue(clang::MacroInfo *macroInfo, NamedMacroMap &macroIndex);
		string getTokenValue(const clang::Token &token, NamedMacroMap &macroIndex);

		virtual bool HandleTopLevelDecl(clang::DeclGroupRef declarations) override;

		void handleFunctionDeclaration(clang::FunctionDecl *declaration);
		void handleRecordDeclaration(clang::RecordDecl *declaration);

		bool isLocationInScope(const clang::SourceLocation location);

	public:
		const SourceMap &getSourceMap() const { return sourceMap; }
		Translator &getTranslator() { return translator; }

		void scan(const string file);
	};
}