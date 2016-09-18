#pragma once

#include <string>
#include <vector>

#include "Formatter.h"
#include "SourceInfoASTConsumer.h"

using std::string;
using std::vector;

namespace ApiScan
{
	class JsonFormatter : public Formatter
	{
	public:
		void outputHeader(ostream& stream);
		
		void outputFooter(ostream& stream);

		void output(string fileName, SourceInfo sourceInfo, ostream& stream, bool isLastFile);
	};
}