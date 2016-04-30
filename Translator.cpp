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

		for (std::string line; getline(stream, line);)
		{
			bool afterSeparator = false;
			std::string key;
			std::string replacement;

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

			std::cout << Util::trim(key) << std::endl;
			translations[Util::trim(key)] = Util::trim(replacement);
		}
	}

	string Translator::translate(const string value)
	{
		if (translations.count(value) > 0)
		{
			return translations[value];
		}

		return value;
	}
}

