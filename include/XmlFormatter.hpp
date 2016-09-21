#pragma once

#include <string>
#include <vector>

#include "Formatter.hpp"

using std::string;
using std::vector;

namespace ApiScan
{
	class XmlFormatter : public Formatter
	{
	public:
		void outputHeader(ostream& stream);

		void outputFooter(ostream& stream);

		void output(const SourceMap sourceMap, ostream& stream);
	};
}