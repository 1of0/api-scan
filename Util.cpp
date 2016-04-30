#include "Util.h"

namespace ApiScan
{
	namespace Util
	{
		string executeCommand(string command)
		{
			shared_ptr<FILE> pipe(popen(command.c_str(), "r"), pclose);

			if (!pipe)
			{
				return "";
			}

			char buffer[128];
			string result = "";

			while (!feof(pipe.get()))
			{
				if (fgets(buffer, 128, pipe.get()) != NULL)
				{
					result += buffer;
				}
			}

			return result;
		}

		string trim(string input)
		{
			unsigned long start;
			for (start = 0; start < input.length(); start++)
			{
				if (input[start] != '\t' && input[start] != ' ')
				{
					break;
				}
			}

			unsigned long end;
			for (end = input.length(); end > 0; end--)
			{
				if (input[end - 1] != '\t' && input[end - 1] != ' ')
				{
					break;
				}
			}

			return input.substr(start, end - start);
		}
	}
}

