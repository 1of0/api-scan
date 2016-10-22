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
		unsigned int alignment;
	};

	struct FieldInfo
	{
		string name;
		TypeInfo type;
		unsigned int alignment;
		bool offsetDefined;
		unsigned long offset;
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

	struct TypedefInfo
	{
		string name;
		TypeInfo type;
		unsigned int alignment;
	};

	class SourceMap
	{
	private:
		map<string, FunctionInfo> functionMap;
		map<string, StructInfo> structMap;
		map<string, DefineInfo> defineMap;
		map<string, TypedefInfo> typedefMap;

	public:
		const map<string, FunctionInfo> &getFunctionMap() const { return functionMap; }
		const map<string, StructInfo> &getStructMap() const { return structMap; }
		const map<string, DefineInfo> &getDefineMap() const { return defineMap; }
		const map<string, TypedefInfo> &getTypedefMap() const { return typedefMap; }

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

		void addTypedef(const TypedefInfo &item)
		{
			if (typedefMap.count(item.name) > 0)
			{
				return;
			}
			typedefMap[item.name] = item;
		}
	};
}