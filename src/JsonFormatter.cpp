#include "JsonFormatter.h"

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

	void JsonFormatter::output(const SourceInfo sourceInfo, ostream& stream)
	{
		stream << I(1) << "\"functions\": [" << std::endl;

		int i = 0;
		for (auto &kv : sourceInfo.getFunctions())
		{
			FunctionInfo function = kv.second;

			stream << I(2) << "{" << std::endl;
			stream << I(3) << "\"name\": " << QUOTE(function.getName()) << "," << std::endl;
			stream << I(3) << "\"type\": " << QUOTE(function.getReturnType()) << "," << std::endl;
			stream << I(3) << "\"params\": [" << std::endl;

			for (int j = 0; j < function.getParameters().size(); j++)
			{
				ParameterInfo parameter = function.getParameters().at(j);

				stream << I(4) << "{" << std::endl;
				stream << I(5) << "\"name\": " << QUOTE(parameter.getName()) << "," << std::endl;
				stream << I(5) << "\"type\": " << QUOTE(parameter.getType()) << "" << std::endl;
				stream << I(4) << "}";

				if (j < function.getParameters().size() - 1)
				{
					stream << ",";
				}

				stream << std::endl;
			}

			stream << I(3) << "]" << std::endl;
			stream << I(2) << "}";

			if (i < sourceInfo.getFunctions().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
			i++;
		}
		
		stream << I(1) << "]," << std::endl;
		stream << I(1) << "\"structs\": [" << std::endl;

		i = 0;
		for (auto &kv : sourceInfo.getStructs())
		{
			StructInfo structInfo = kv.second;

			stream << I(2) << "{" << std::endl;
			stream << I(3) << "\"name\": " << QUOTE(structInfo.getName()) << "," << std::endl;
			stream << I(3) << "\"fields\": [" << std::endl;

			for (int j = 0; j < structInfo.getFields().size(); j++)
			{
				FieldInfo fieldInfo =  structInfo.getFields().at(j);

				stream << I(4) << "{" << std::endl;
				stream << I(5) << "\"name\": " << QUOTE(fieldInfo.getName()) << "," << std::endl;
				stream << I(5) << "\"type\": " << QUOTE(fieldInfo.getType()) << "" << std::endl;
				stream << I(4) << "}";

				if (j <  structInfo.getFields().size() - 1)
				{
					stream << ",";
				}

				stream << std::endl;
			}			

			stream << I(3) << "]" << std::endl;
			stream << I(2) << "}";

			if (i < sourceInfo.getStructs().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
			i++;
		}

		stream << I(1) << "]" << std::endl;
	}
}

