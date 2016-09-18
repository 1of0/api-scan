#include "Translator.h"

namespace ApiScan
{
	void Translator::load(const string file)
	{
		ifstream stream(file);

		if (!stream)
		{
			return;
		}

		for (string line; getline(stream, line);)
		{
			bool afterSeparator = false;
			string key;
			string replacement;

			for (int i = 0; i < line.length(); i++)
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

			translations[this->trim(key)] = this->trim(replacement);
		}
	}

	const string Translator::translate(const string value)
	{
		if (translations.count(value) > 0)
		{
			return translations[value];
		}

		return value;
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

