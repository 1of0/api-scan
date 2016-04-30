#pragma once

#include <string>
#include <vector>

#include "FunctionInfoASTConsumer.h"

using std::string;
using std::vector;

namespace ApiScan
{
	class XmlFormatter
	{
	private:
		string getIndentation(uint level);

	public:
		string *format(vector<FunctionInfo> functions, uint indentation = 0);
	};
}