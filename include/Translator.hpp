#pragma once

#include <fstream>
#include <string>
#include <map>

#include "Util.hpp"

using std::ifstream;
using std::string;
using std::map;

namespace ApiScan
{
	enum Dictionary
	{
		DictType,
		DictParam,
		DictField
	};

	class Translator
	{
	private:
		map<Dictionary, map<string, string>> dictionaries;

		const string trim(const string input);

	public:
		void load(Dictionary dictionary, const string file);

		const string translate(Dictionary dictionary, const string value);
	};
}
