#include "Translator.hpp"

namespace ApiScan
{
	void Translator::load(Dictionary dictionary, const string file)
	{
		ifstream stream(file);

		if (!stream || !stream.good())
		{
			return;
		}

		dictionaries[dictionary] = map<string, string>();

		for (string line; getline(stream, line);)
		{
			bool afterSeparator = false;
			string key;
			string replacement;

			for (unsigned int i = 0; i < line.length(); i++)
			{
				if (line[i] == '=')
				{
					afterSeparator = true;
					continue;
				}

				if (!afterSeparator)
				{
					key += line[i];
				}
				else
				{
					replacement += line[i];
				}
			}

			dictionaries[dictionary][this->trim(key)] = this->trim(replacement);
		}
	}

	const string Translator::translate(Dictionary dictionary, const string value)
	{
		if (dictionaries.count(dictionary) == 0 || dictionaries[dictionary].count(value) == 0)
		{
			return value;
		}

		return dictionaries[dictionary][value];
	}

	const string Translator::trim(const string input)
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

