#pragma once

#include <string>
#include <vector>

#include "SourceInfoASTConsumer.h"

#define I(x) I_ ## x
#define I_1 "\t"
#define I_2 "\t\t"
#define I_3 "\t\t\t"
#define I_4 "\t\t\t\t"
#define I_5 "\t\t\t\t\t"
#define I_6 "\t\t\t\t\t\t"
#define I_7 "\t\t\t\t\t\t\t"
#define I_8 "\t\t\t\t\t\t\t\t"
#define I_9 "\t\t\t\t\t\t\t\t\t"

#define QUOTE(x) "\"" + x + "\"" 

using std::string;
using std::vector;
using std::ostream;

namespace ApiScan
{
	class Formatter
	{
	public:
		virtual void outputHeader(ostream& stream) = 0;
		
		virtual void outputFooter(ostream& stream) = 0;

		virtual void output(string fileName, SourceInfo sourceInfo, ostream& stream, bool isLastFile) = 0;
	};
}