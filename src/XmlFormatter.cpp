#include "XmlFormatter.h"

namespace ApiScan
{
	string *XmlFormatter::format(vector<ApiScan::FunctionInfo> functions, uint level)
	{
		string *buffer = new string();

		string indentation = getIndentation(level);

		for (FunctionInfo function : functions)
		{
			*buffer += indentation + "<function ";
			*buffer += "name=\"" + function.getName() + "\" ";
			*buffer += "type=\"" + function.getReturnType() + "\"";
			*buffer += ">\n";

			for (ParameterInfo parameter : function.getParameters())
			{
				*buffer += indentation + "\t<param ";
				*buffer += "name=\"" + parameter.getName() + "\" ";
				*buffer += "type=\"" + parameter.getType() + "\"";
				*buffer += " />\n";
			}
			*buffer += indentation + "</function>\n";
		}

		return buffer;
	}

	string XmlFormatter::getIndentation(uint level)
	{
		char buffer[level + 1];

		for (int i = 0; i < level; i++)
		{
			buffer[i] = '\t';
		}
		buffer[level] = '\0';

		return string(buffer);
	}
}

