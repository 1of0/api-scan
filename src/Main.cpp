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

		TCLAP::ValueArg<string> argTypeDictionary("t", "type-dict", "File containing translations for function types", false, "", "string");
		TCLAP::ValueArg<string> argParamDictionary("p", "param-dict", "File containing translations for parameter names", false, "", "string");
		TCLAP::ValueArg<string> argFieldDictionary("f", "field-dict", "File containing translations for struct field names", false, "", "string");

		TCLAP::ValueArg<string> argFormat("o", "out-format", "Output format - xml/json", false, "xml", "string");

		cmd.add(argSourceFiles);
		cmd.add(argTypeDictionary);
		cmd.add(argParamDictionary);
		cmd.add(argFieldDictionary);
		cmd.add(argFormat);

		cmd.parse(argc, argv);

		SourceScanner scanner;

		if (argTypeDictionary.isSet())
		{
			Translator typeTranslator = Translator(argTypeDictionary.getValue());
			scanner.setTypeTranslator(typeTranslator);
		}

		if (argParamDictionary.isSet())
		{
			Translator paramTranslator = Translator(argParamDictionary.getValue());
			scanner.setParamTranslator(paramTranslator);
		}

		if (argFieldDictionary.isSet())
		{
			Translator fieldTranslator = Translator(argFieldDictionary.getValue());
			scanner.setFieldTranslator(fieldTranslator);
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

		for (string file : files)
		{
			scanner.scan(file);
		}

		formatter->outputHeader(std::cout);
		formatter->output(scanner.getSourceInfo(), std::cout);
		formatter->outputFooter(std::cout);
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}
