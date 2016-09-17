#pragma once

#include <string>
#include <vector>

#include "SourceInfoASTConsumer.h"

using std::string;
using std::vector;

namespace ApiScan
{
	class XmlFormatter
	{
	private:
		string getIndentation(uint level);

	public:
		string *format(SourceInfo sourceInfo, uint indentation = 0);
	};
}