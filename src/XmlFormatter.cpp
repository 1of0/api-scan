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

		for (auto &kv : sourceMap.getTypedefMap())
		{
			TypedefInfo typedefInfo = kv.second;

			stream << I(1)
				<< "<typedef"
				<< " name=" << QUOTE(typedefInfo.name)
				<< " type=" << QUOTE(typedefInfo.type.name)
			;

			if (typedefInfo.type.constantArraySize)
			{
				stream << " constantArraySize=" << STREAM_QUOTE(typedefInfo.type.constantArraySize);
			}

			if (typedefInfo.alignment)
			{
				stream << " alignment=" << STREAM_QUOTE(typedefInfo.alignment);
			}

			stream << " />" << std::endl;
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

				if (parameter.alignment)
				{
					stream << " alignment=" << STREAM_QUOTE(parameter.alignment);
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

				if (fieldInfo.alignment)
				{
					stream << " alignment=" << STREAM_QUOTE(fieldInfo.alignment);
				}

				if (fieldInfo.offsetDefined)
				{
					stream << " offset=" << STREAM_QUOTE(fieldInfo.offset);
				}

				stream << " />" << std::endl;
			}

			stream << I(1) << "</struct>" << std::endl;
		}
	}
}

