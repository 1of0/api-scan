#pragma once

#include <string>
#include <vector>

#include "Formatter.h"

using std::string;
using std::vector;

namespace ApiScan
{
	class JsonFormatter : public Formatter
	{
	public:
		void outputHeader(ostream& stream);
		
		void outputFooter(ostream& stream);

		void output(const SourceInfo sourceInfo, ostream& stream);
	};
}