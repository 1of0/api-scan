#pragma once

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

using std::shared_ptr;
using std::string;
using std::stringstream;
using std::vector;

namespace ApiScan
{
	namespace Util
	{
		string &replaceAll(string &subject, const string &search, const string &replacement);

		string executeCommand(string command);

		vector<string> getGccIncludes();
	}
}