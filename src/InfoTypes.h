#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace ApiScan
{
	class SourceInfo;
	class FunctionInfo;
	class ParameterInfo;
	class StructInfo;
	class FieldInfo;

	class SourceInfo
	{
	private:
		vector<FunctionInfo> functions;
		vector<StructInfo> structs;

	public:
		const vector<FunctionInfo> &getFunctions() const { return this->functions; }
		const vector<StructInfo> &getStructs() const { return this->structs; }
		
		void addFunction(const FunctionInfo &functionInfo)
		{
			this->functions.push_back(functionInfo);
		}
		
		void addStruct(const StructInfo &structInfo)
		{
			this->structs.push_back(structInfo);
		}
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

	class StructInfo
	{
	private:
		string name;
		vector<FieldInfo> fields;

	public:
		StructInfo() { }

		StructInfo(const string &name) : name(name) { }

		const string &getName() const { return this->name; }
		const vector<FieldInfo> &getFields() { return this->fields; }

		void addField(const FieldInfo &field)
		{
			this->fields.push_back(field);
		}
	};

	class FieldInfo
	{
	private:
		string name;
		string type;

	public:
		FieldInfo() { }
		FieldInfo(const string &name, const string &type) : name(name), type(type) { }

		const string &getName() const { return this->name; }
		const string &getType() const { return this->type; }
	};
}