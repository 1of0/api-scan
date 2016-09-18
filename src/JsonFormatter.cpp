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

	void JsonFormatter::output(string fileName, SourceInfo sourceInfo, ostream& stream, bool isLastFile)
	{
		stream << I(1) << QUOTE(fileName) << ": {" << std::endl;

		stream << I(2) << "\"functions\": [" << std::endl;

		for (int i = 0; i < sourceInfo.getFunctions().size(); i++)
		{
			FunctionInfo function = sourceInfo.getFunctions().at(i);

			stream << I(3) << "{" << std::endl;
			stream << I(4) << "\"name\": " << QUOTE(function.getName()) << "," << std::endl;
			stream << I(4) << "\"type\": " << QUOTE(function.getReturnType()) << "," << std::endl;
			stream << I(4) << "\"params\": [" << std::endl;

			for (int j = 0; j < function.getParameters().size(); j++)
			{
				ParameterInfo parameter = function.getParameters().at(j);

				stream << I(5) << "{" << std::endl;
				stream << I(6) << "\"name\": " << QUOTE(parameter.getName()) << "," << std::endl;
				stream << I(6) << "\"type\": " << QUOTE(parameter.getType()) << "" << std::endl;
				stream << I(5) << "}";

				if (j < function.getParameters().size() - 1)
				{
					stream << ",";
				}

				stream << std::endl;
			}

			stream << I(4) << "]" << std::endl;
			stream << I(3) << "}";

			if (i < sourceInfo.getFunctions().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
		}
		
		stream << I(2) << "]," << std::endl;
		stream << I(2) << "\"structs\": [" << std::endl;

		for (int i = 0; i < sourceInfo.getStructs().size(); i++)
		{
			StructInfo structInfo = sourceInfo.getStructs().at(i);

			stream << I(3) << "{" << std::endl;
			stream << I(4) << "\"name\": " << QUOTE(structInfo.getName()) << "," << std::endl;
			stream << I(4) << "\"fields\": [" << std::endl;

			for (int j = 0; j < structInfo.getFields().size(); j++)
			{
				FieldInfo fieldInfo =  structInfo.getFields().at(j);

				stream << I(5) << "{" << std::endl;
				stream << I(6) << "\"name\": " << QUOTE(fieldInfo.getName()) << "," << std::endl;
				stream << I(6) << "\"type\": " << QUOTE(fieldInfo.getType()) << "" << std::endl;
				stream << I(5) << "}";

				if (j <  structInfo.getFields().size() - 1)
				{
					stream << ",";
				}

				stream << std::endl;
			}			

			stream << I(4) << "]" << std::endl;
			stream << I(3) << "}";

			if (i < sourceInfo.getStructs().size() - 1)
			{
				stream << ",";
			}

			stream << std::endl;
		}

		stream << I(2) << "]" << std::endl;
		
		stream << I(1) << "}";

		if (!isLastFile)
		{
			stream << ",";
		}

		stream << std::endl;
	}
}

