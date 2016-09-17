#include "XmlFormatter.h"

namespace ApiScan
{
	string *XmlFormatter::format(SourceInfo sourceInfo, uint level)
	{
		string *buffer = new string();

		string indentation = getIndentation(level);

		for (FunctionInfo function : sourceInfo.getFunctions())
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

		for (StructInfo structInfo : sourceInfo.getStructs())
		{
			*buffer += indentation + "<struct name=\"";
			*buffer += structInfo.getName();
			*buffer += "\">\n";

			for (FieldInfo fieldInfo : structInfo.getFields())
			{
				*buffer += indentation + "\t<field ";
				*buffer += "name=\"" + fieldInfo.getName() + "\" ";
				*buffer += "type=\"" + fieldInfo.getType() + "\"";
				*buffer += " />\n";
			}
			*buffer += indentation + "</struct>\n";
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

