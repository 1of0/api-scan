#pragma once

#include <map>
#include <ostream>
#include <string>
#include <vector>

#include "InfoTypes.hpp"
#include "Util.hpp"

#define I(x) I_ ## x
#define I_1 "\t"
#define I_2 "\t\t"
#define I_3 "\t\t\t"
#define I_4 "\t\t\t\t"
#define I_5 "\t\t\t\t\t"
#define I_6 "\t\t\t\t\t\t"
#define I_7 "\t\t\t\t\t\t\t"
#define I_8 "\t\t\t\t\t\t\t\t"
#define I_9 "\t\t\t\t\t\t\t\t\t"

#define QUOTE(x) ("\"" + x + "\"")
#define UNQOUTE(x) (x.substr(1, x.length() - 2))
#define JSON_ESCAPE(x) ApiScan::Util::replaceAll(x, "\"", "\\\"")

using std::map;
using std::ostream;
using std::string;
using std::vector;

namespace ApiScan
{
	class Formatter
	{
	public:
		virtual void outputHeader(ostream& stream) = 0;

		virtual void outputFooter(ostream& stream) = 0;

		virtual void output(const SourceMap sourceMap, ostream& stream) = 0;
	};
}