#include "JsonFormatter.hpp"

namespace ApiScan
{
	void JsonFormatter::outputHeader(ostream& stream)
	{
		stream << "{" << std::endl;
	}

	void JsonFormatter::outputFooter(ostream& stream)
	{
		stream << "}" << std::endl;
	}

	void JsonFormatter::output(const SourceMap sourceMap, ostream& stream)
	{
		unsigned int i = 0;

		stream << I(1) << "\"defines\": [" << std::endl;

		i = 0;
		for (auto &kv : sourceMap.getDefineMap())
		{
			DefineInfo defineInfo = kv.second;

			stream << I(2) << "{ ";
			stream << "\"name\": " << QUOTE(defineInfo.name) << ", ";
			stream << "\"value\": " << QUOTE(JSON_ESCAPE(defineInfo.expansion));
			stream << " }";

			if (i < sourceMap.getDefineMap().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
			i++;
		}

		stream << I(1) << "]," << std::endl;
		stream << I(1) << "\"typedefs\": [" << std::endl;

		i = 0;
		for (auto &kv : sourceMap.getTypedefMap())
		{
			TypedefInfo typedefInfo = kv.second;

			stream << I(2) << "{ " << std::endl;
			stream << I(3) << "\"name\": " << QUOTE(typedefInfo.name) << "," << std::endl;
			stream << I(3) << "\"type\": " << QUOTE(typedefInfo.type.name);

			if (typedefInfo.type.constantArraySize)
			{
				stream << "," << std::endl;
				stream << I(3) << "\"constantArraySize\": " << typedefInfo.type.constantArraySize;
			}

			if (typedefInfo.alignment)
			{
				stream << "," << std::endl;
				stream << I(3) << "\"alignment\": " << typedefInfo.alignment;
			}

			stream << std::endl;

			stream << I(2) << "}";

			if (i < sourceMap.getTypedefMap().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
			i++;
		}

		stream << I(1) << "]," << std::endl;
		stream << I(1) << "\"functions\": [" << std::endl;

		i = 0;
		for (auto &kv : sourceMap.getFunctionMap())
		{
			FunctionInfo function = kv.second;

			stream << I(2) << "{" << std::endl;
			stream << I(3) << "\"name\": " << QUOTE(function.name) << "," << std::endl;
			stream << I(3) << "\"returnType\": " << QUOTE(function.returnType.name) << "," << std::endl;

			if (function.returnType.constantArraySize)
			{
				stream << I(3) << "\"returnConstantArraySize\": " << function.returnType.constantArraySize << "," << std::endl;
			}

			if (function.parameters.size() == 0)
			{
				stream << I(3) << "\"params\": []" << std::endl;
			}
			else
			{
				stream << I(3) << "\"params\": [" << std::endl;

				for (unsigned int j = 0; j < function.parameters.size(); j++)
				{
					ParameterInfo parameter = function.parameters[j];

					stream << I(4) << "{" << std::endl;
					stream << I(5) << "\"name\": " << QUOTE(parameter.name) << "," << std::endl;
					stream << I(5) << "\"type\": " << QUOTE(parameter.type.name);

					if (parameter.type.constantArraySize)
					{
						stream << "," << std::endl;
						stream << I(5) << "\"constantArraySize\": " << parameter.type.constantArraySize;
					}

					if (parameter.alignment)
					{
						stream << "," << std::endl;
						stream << I(5) << "\"alignment\": " << parameter.alignment;
					}

					stream << std::endl;

					stream << I(4) << "}";

					if (j < function.parameters.size() - 1)
					{
						stream << ",";
					}

					stream << std::endl;
				}

				stream << I(3) << "]" << std::endl;
			}
			stream << I(2) << "}";

			if (i < sourceMap.getFunctionMap().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
			i++;
		}

		stream << I(1) << "]," << std::endl;
		stream << I(1) << "\"structs\": [" << std::endl;

		i = 0;
		for (auto &kv : sourceMap.getStructMap())
		{
			StructInfo structInfo = kv.second;

			stream << I(2) << "{" << std::endl;
			stream << I(3) << "\"name\": " << QUOTE(structInfo.name) << "," << std::endl;

			if (structInfo.fields.size() == 0)
			{
				stream << I(3) << "\"fields\": []" << std::endl;
			}
			else
			{
				stream << I(3) << "\"fields\": [" << std::endl;

				for (unsigned int j = 0; j < structInfo.fields.size(); j++)
				{
					FieldInfo fieldInfo =  structInfo.fields[j];

					stream << I(4) << "{" << std::endl;
					stream << I(5) << "\"name\": " << QUOTE(fieldInfo.name) << "," << std::endl;
					stream << I(5) << "\"type\": " << QUOTE(fieldInfo.type.name);

					if (fieldInfo.type.constantArraySize)
					{
						stream << "," << std::endl;
						stream << I(5) << "\"constantArraySize\": " << fieldInfo.type.constantArraySize;
					}

					if (fieldInfo.alignment)
					{
						stream << "," << std::endl;
						stream << I(5) << "\"alignment\": " << fieldInfo.alignment;
					}

					if (fieldInfo.offsetDefined)
					{
						stream << "," << std::endl;
						stream << I(5) << "\"offset\": " << fieldInfo.offset;
					}

					stream << std::endl;

					stream << I(4) << "}";

					if (j <  structInfo.fields.size() - 1)
					{
						stream << ",";
					}

					stream << std::endl;
				}

				stream << I(3) << "]" << std::endl;
			}
			stream << I(2) << "}";

			if (i < sourceMap.getStructMap().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
			i++;
		}

		stream << I(1) << "]" << std::endl;
	}
}

