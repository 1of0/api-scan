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
	}
}

