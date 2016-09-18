#include "XmlFormatter.h"

namespace ApiScan
{
	void XmlFormatter::outputHeader(ostream& stream)
	{
		stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
	}

	void XmlFormatter::outputFooter(ostream& stream)
	{
	}

	void XmlFormatter::output(const SourceInfo sourceInfo, ostream& stream)
	{
		stream << "<api>" << std::endl;

		for (auto &kv : sourceInfo.getFunctions())
		{
			FunctionInfo function = kv.second;

			stream << I(1) 
				<< "<function"
				<< " name=" << QUOTE(function.getName()) 
				<< " type=" << QUOTE(function.getReturnType()) 
				<< ">" << std::endl
			;

			for (ParameterInfo parameter : function.getParameters())
			{
				stream << I(2) 
					<< "<param"
					<< " name=" << QUOTE(parameter.getName()) 
					<< " type=" << QUOTE(parameter.getType()) 
					<< " />" << std::endl
				;
			}

			stream << I(1) << "</function>" << std::endl;
		}

		for (auto &kv : sourceInfo.getStructs())
		{
			StructInfo structInfo = kv.second;

			stream << I(1) 
				<< "<struct"
				<< " name=" << QUOTE(structInfo.getName())
				<< ">" << std::endl
			;

			for (FieldInfo fieldInfo : structInfo.getFields())
			{
				stream << I(2) 
					<< "<field"
					<< " name=" << QUOTE(fieldInfo.getName()) 
					<< " type=" << QUOTE(fieldInfo.getType()) 
					<< " />" << std::endl
				;
			}
			
			stream << I(1) << "</struct>" << std::endl;
		}

		stream << "</api>" << std::endl;
	}
}

