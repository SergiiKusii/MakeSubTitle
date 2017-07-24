// makeSubTitle.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "cSubFile.h"

namespace tag {
	const std::string sConvCyryllic = "-c";
}
struct InputData
{
	std::string sFileLeft;
	std::string sFileRight;
	std::string sFileOut;

	bool bTransformCyryllic = false;
};

static InputData g_inputCfg;

//TODO: standart read
void readInputData(size_t size, char **data){
	data++; //skip run file
	std::cout << "File left = " << *data << std::endl;
	g_inputCfg.sFileLeft = *data;
	data++;
	std::cout << "File right = " << *data << std::endl;
	g_inputCfg.sFileRight = *data;
	data++;
	std::cout << "File out = " << *data << std::endl;
	g_inputCfg.sFileOut = *data;
	if (size == 5) {
		data++;
		g_inputCfg.bTransformCyryllic = (tag::sConvCyryllic == *data);
	}
}

int main(size_t size, char **data)
{
	std::cout << "Make combine subtitre file" << std::endl;
	if (size < 4) {
		std::cout << "ERR: wrong parameters." << std::endl;
		std::cout << "This application marge two subscribe files." << std::endl;
		std::cout << "Mandatory parameters:" << std::endl;
		std::cout << "1 - basic subscribe file path;" << std::endl;
		std::cout << "2 - additional subscribe file path;" << std::endl;
		std::cout << "3 - out subscribe file path;" << std::endl;
		std::cout << "4 - convert cyrillic symbols to latin (-c)" << std::endl;
		std::cout << "Copyright (c) 2016 Kusii S.M." << std::endl;
	}
	else
	{
		try
		{
			readInputData(size, data);

			cSubFile subFileLeft;
			cSubFile subFileRight(g_inputCfg.bTransformCyryllic);
			subFileLeft.readFromFile(g_inputCfg.sFileLeft);
			subFileRight.readFromFile(g_inputCfg.sFileRight);
			if (g_inputCfg.bTransformCyryllic){
				subFileLeft.addSeparator();
			}
			subFileLeft.merge(subFileRight);
			subFileLeft.saveToFile(g_inputCfg.sFileOut);

			std::cout << "SUCCESS :)" << std::endl;
		}
		catch (const std::exception& except)
		{
			std::cout << "ERR:" << except.what() << std::endl;
		}
		catch (const std::string& sExcept)
		{
			std::cout << "ERR:" << sExcept << std::endl;
		}
		catch (...)
		{
			std::cout << "ERR: UNCNOWN" << std::endl;
		}
	}
	system("pause");
    return 0;
}

