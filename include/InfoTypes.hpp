#pragma once

#include <string>
#include <vector>
#include <map>

using std::string;
using std::vector;
using std::map;

namespace ApiScan
{
	struct TypeInfo
	{
		string name;
		unsigned int constantArraySize;
	};

	struct ParameterInfo
	{
		string name;
		TypeInfo type;
	};

	struct FieldInfo
	{
		string name;
		TypeInfo type;
	};

	struct DefineInfo
	{
		string name;
		string expansion;
	};

	struct FunctionInfo
	{
		string name;
		TypeInfo returnType;

		vector<ParameterInfo> parameters;
	};

	struct StructInfo
	{
		string name;
		vector<FieldInfo> fields;
	};

	class SourceMap
	{
	private:
		map<string, FunctionInfo> functionMap;
		map<string, StructInfo> structMap;
		map<string, DefineInfo> defineMap;

	public:
		const map<string, FunctionInfo> &getFunctionMap() const { return functionMap; }
		const map<string, StructInfo> &getStructMap() const { return structMap; }
		const map<string, DefineInfo> &getDefineMap() const { return defineMap; }

		void addFunction(const FunctionInfo &item)
		{
			if (functionMap.count(item.name) > 0)
			{
				return;
			}
			functionMap[item.name] = item;
		}

		void addStruct(const StructInfo &item)
		{
			if (structMap.count(item.name) > 0)
			{
				return;
			}
			structMap[item.name] = item;
		}

		void addDefine(const DefineInfo &item)
		{
			if (defineMap.count(item.name) > 0)
			{
				return;
			}
			defineMap[item.name] = item;
		}
	};
}