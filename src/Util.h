#pragma once

#include <iostream>
#include <memory>
#include <string>

using std::shared_ptr;
using std::string;

namespace ApiScan
{
	namespace Util
	{
		string executeCommand(string command);
		string trim(string input);
	}
}