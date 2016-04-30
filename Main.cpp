#include "Main.h"

int main(int argc, const char** argv)
{
	try
	{
		TCLAP::CmdLine cmd(
			"Scans C code/header files for exposed functions, and returns an XML formatted structure with function and "
			"parameter information.",
			' ', "1.0"
		);

		TCLAP::UnlabeledMultiArg<string> sourceFiles("source-files", "Source files to scan", true, "string");

		TCLAP::ValueArg<string> funcDictionary("f", "function-dict", "File containing translations for function names", false, "", "string");
		TCLAP::ValueArg<string> paramDictionary("p", "param-dict", "File containing translations for parameter names", false, "", "string");
		TCLAP::ValueArg<string> typeDictionary("t", "type-dict", "File containing translations for function types", false, "", "string");

		cmd.add(sourceFiles);
		cmd.add(funcDictionary);
		cmd.add(paramDictionary);
		cmd.add(typeDictionary);

		cmd.parse(argc, argv);

		FunctionScanner scanner;

		if (funcDictionary.isSet())
		{
			Translator funcTranslator = Translator(funcDictionary.getValue());
			scanner.setFuncTranslator(funcTranslator);
		}

		if (paramDictionary.isSet())
		{
			Translator paramTranslator = Translator(paramDictionary.getValue());
			scanner.setParamTranslator(paramTranslator);
		}

		if (typeDictionary.isSet())
		{
			Translator typeTranslator = Translator(typeDictionary.getValue());
			scanner.setTypeTranslator(typeTranslator);
		}

		vector<string> files = sourceFiles.getValue();
		XmlFormatter xml;
		string buffer;

		for (string file : files)
		{
			string *result = xml.format(scanner.scan(file));
			buffer += *result;
			delete result;
		}

		std::cout << buffer;
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}
