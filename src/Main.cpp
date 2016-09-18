#include "Main.h"

int main(int argc, const char** argv)
{
	try
	{
		TCLAP::CmdLine cmd(
			"Scans C code/header files for exposed functions and structs, and returns function and type information as "
			"XML or JSON.",
			' ', "1.0"
		);

		TCLAP::UnlabeledMultiArg<string> argSourceFiles("source-files", "Source files to scan", true, "string");

		TCLAP::ValueArg<string> argParamDictionary("p", "param-dict", "File containing translations for parameter names", false, "", "string");
		TCLAP::ValueArg<string> argTypeDictionary("t", "type-dict", "File containing translations for function types", false, "", "string");

		TCLAP::ValueArg<string> argFormat("f", "format", "Output format - xml/json", false, "xml", "string");

		cmd.add(argSourceFiles);
		cmd.add(argParamDictionary);
		cmd.add(argTypeDictionary);
		cmd.add(argFormat);

		cmd.parse(argc, argv);

		SourceScanner scanner;

		if (argParamDictionary.isSet())
		{
			Translator paramTranslator = Translator(argParamDictionary.getValue());
			scanner.setParamTranslator(paramTranslator);
		}

		if (argTypeDictionary.isSet())
		{
			Translator typeTranslator = Translator(argTypeDictionary.getValue());
			scanner.setTypeTranslator(typeTranslator);
		}

		Formatter *formatter;

		if (argFormat.isSet() && argFormat.getValue() == "json")
		{
			formatter = new JsonFormatter();
		}
		else
		{
			formatter = new XmlFormatter();
		}

		vector<string> files = argSourceFiles.getValue();

		formatter->outputHeader(std::cout);

		int numFiles = files.size();
		for (int i = 0; i < numFiles; i++)
		{
			string file = files.at(i);
			formatter->output(file, scanner.scan(file), std::cout, i == numFiles - 1);
		}

		formatter->outputFooter(std::cout);
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}
