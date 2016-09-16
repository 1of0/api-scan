#include "Main.h"

int main(int argc, const char** argv)
{
	try
	{
		TCLAP::CmdLine cmd(
			"Scans C code/header files for exposed functions, and returns a XML formatted structure with function and "
			"parameter information.",
			' ', "1.0"
		);

		TCLAP::UnlabeledMultiArg<string> sourceFiles("source-files", "Source files to scan", true, "string");

		TCLAP::ValueArg<string> paramDictionary("p", "param-dict", "File containing translations for parameter names", false, "", "string");
		TCLAP::ValueArg<string> typeDictionary("t", "type-dict", "File containing translations for function types", false, "", "string");

		cmd.add(sourceFiles);
		cmd.add(paramDictionary);
		cmd.add(typeDictionary);

		cmd.parse(argc, argv);

		FunctionScanner scanner;

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
			string *result = xml.format(scanner.scan(file), 1);
			buffer += *result;
			delete result;
		}

		std::cout << "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>" << std::endl;
		std::cout << "<library>" << std::endl;
		std::cout << buffer;
		std::cout << "</library>" << std::endl;
	}
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
	}

	return 0;
}
