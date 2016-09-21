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
		string executeCommand(string command);

		vector<string> getGccIncludes();
	}
}