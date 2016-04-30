#pragma once

#include <fstream>
#include <string>
#include <map>

#include "Util.h"

using std::ifstream;
using std::string;
using std::map;

namespace ApiScan
{
	class Translator
	{
	private:
		map<string, string> translations;

	public:
		Translator() { }
		Translator(const string source) { load(source); }

		virtual void load(const string file);

		virtual string translate(const string value);
	};

	class NullTranslator : public Translator
	{
	public:
		virtual void load(const string file) override
		{
			Translator::load(file);
		}

		virtual string translate(const string value) override
		{
			return value;
		}
	};
}
