#pragma once

#include <iostream>
#include <string>
#include <vector>

#include <clang/AST/ASTConsumer.h>
#include <clang/AST/Attr.h>

#include "Translator.h"

using clang::ASTConsumer;
using clang::Decl;
using clang::DeclGroupRef;
using clang::FunctionDecl;
using clang::ParmVarDecl;
using clang::VisibilityAttr;

using llvm::dyn_cast;

using std::string;
using std::vector;

namespace ApiScan
{
	class FunctionInfoASTConsumer;
	class FunctionInfo;
	class ParameterInfo;

	class FunctionInfoASTConsumer: public ASTConsumer
	{
	private:
		Translator paramTranslator;
		Translator typeTranslator;

		vector<FunctionInfo> functions;

		virtual bool HandleTopLevelDecl(DeclGroupRef declarations) override;

	public:
		FunctionInfoASTConsumer()
		{
			paramTranslator = NullTranslator();
			typeTranslator = NullTranslator();
		}

		void setParamTranslator(Translator &paramTranslator) { this->paramTranslator = paramTranslator; }
		void setTypeTranslator(Translator &typeTranslator) { this->typeTranslator = typeTranslator; }

		const vector<FunctionInfo> &getFunctions() const { return this->functions; }
	};

	class FunctionInfo
	{
	private:
		string name;
		string returnType;
		vector<ParameterInfo> parameters;

	public:
		FunctionInfo() { }

		FunctionInfo(const string &name, const string &returnType) : name(name), returnType(returnType) { }

		const string &getName() const { return this->name; }
		const string &getReturnType() const { return this->returnType; }

		const vector<ParameterInfo> &getParameters() { return this->parameters; }

		void addParameter(const ParameterInfo &parameter)
		{
			this->parameters.push_back(parameter);
		}
	};

	class ParameterInfo
	{
	private:
		string name;
		string type;

	public:
		ParameterInfo() { }
		ParameterInfo(const string &name, const string &type) : name(name), type(type) { }

		const string &getName() const { return this->name; }
		const string &getType() const { return this->type; }
	};
}