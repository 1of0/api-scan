#include "Util.hpp"

namespace ApiScan
{
	namespace Util
	{
		string &replaceAll(string &subject, const string &search, const string &replacement)
		{
			if (subject.empty() || search.empty())
			{
				return subject;
			}

			for (size_t start = 0; (start = subject.find(search, start)) != string::npos; start += replacement.length())
			{
				subject.replace(start, search.length(), replacement);
			}

			return subject;
		}

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

		vector<string> getGccIncludes()
		{
			string result = executeCommand("echo | gcc -Wp,-v -x c - -fsyntax-only 2>&1");
			vector<string> includes;

			stringstream stream(result);
			string line;
			bool listingIncludes = false;

			while (std::getline(stream, line, '\n'))
			{
				if (line == "#include \\\"...\\\" search starts here:" || line == "#include <...> search starts here:")
				{
					listingIncludes = true;
					continue;
				}

				if (line == "End of search list.")
				{
					listingIncludes = false;
					continue;
				}

				if (listingIncludes)
				{
					includes.push_back(line.substr(1));
				}
			}

			return includes;
		}
	}
}

