#include "XmlFormatter.hpp"

namespace ApiScan
{
	void XmlFormatter::outputHeader(ostream& stream)
	{
		stream << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
		stream << "<api>" << std::endl;
	}

	void XmlFormatter::outputFooter(ostream& stream)
	{
		stream << "</api>" << std::endl;
	}

	void XmlFormatter::output(const SourceMap sourceMap, ostream& stream)
	{

		for (auto &kv : sourceMap.getDefineMap())
		{
			DefineInfo defineInfo = kv.second;

			stream << I(1) << "<define name=" << QUOTE(defineInfo.name) << ">";
			stream << defineInfo.expansion;
			stream << "</define>" << std::endl;
		}

		for (auto &kv : sourceMap.getFunctionMap())
		{
			FunctionInfo function = kv.second;

			stream << I(1)
				<< "<function"
				<< " name=" << QUOTE(function.name)
				<< " returnType=" << QUOTE(function.returnType.name)
			;

			if (function.returnType.constantArraySize)
			{
				stream << " returnConstantArraySize=" << STREAM_QUOTE(function.returnType.constantArraySize);
			}

			stream << ">" << std::endl;

			for (ParameterInfo parameter : function.parameters)
			{
				stream << I(2)
					<< "<param"
					<< " name=" << QUOTE(parameter.name)
					<< " type=" << QUOTE(parameter.type.name)
				;

				if (parameter.type.constantArraySize)
				{
					stream << " constantArraySize=" << STREAM_QUOTE(parameter.type.constantArraySize);
				}

				stream << " />" << std::endl;
			}

			stream << I(1) << "</function>" << std::endl;
		}

		for (auto &kv : sourceMap.getStructMap())
		{
			StructInfo structInfo = kv.second;

			stream << I(1)
				<< "<struct"
				<< " name=" << QUOTE(structInfo.name)
				<< ">" << std::endl
			;

			for (FieldInfo fieldInfo : structInfo.fields)
			{
				stream << I(2)
					<< "<field"
					<< " name=" << QUOTE(fieldInfo.name)
					<< " type=" << QUOTE(fieldInfo.type.name)
				;

				if (fieldInfo.type.constantArraySize)
				{
					stream << " constantArraySize=" << STREAM_QUOTE(fieldInfo.type.constantArraySize);
				}

				stream << " />" << std::endl;
			}

			stream << I(1) << "</struct>" << std::endl;
		}
	}
}

