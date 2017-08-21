// makeSubTitle.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "cSubFile.h"
#include "Converter.h"

namespace tag {
	const std::string sConvert = "-conv";
	const std::string sUtf8Bom = "utf8bom";
	const std::string sCp1251 = "cp1251";
	const std::string sCyrLat = "-CyrLat";
	const std::string sClose = "-close";
}

struct InputData
{
	std::string sFileLeft;
	std::string sFileRight;
	std::string sFileOut;

	convertCfg convCfg;

	bool bClose = false;
};

static InputData g_inputCfg;

//TODO: standart read
void readInputData(size_t size, char **data){
	const size_t constParCount = 4;
	if (size < constParCount) {
		std::cout << "ERROR: Wrong parameters." << std::endl;
		std::cout << " " << std::endl;
		std::cout << "This application marge two subscribe files." << std::endl;
		std::cout << "Mandatory parameters:" << std::endl;
		std::cout << "1 - basic subscribe file path;" << std::endl;
		std::cout << "2 - additional subscribe file path;" << std::endl;
		std::cout << "3 - out subscribe file path;" << std::endl;
		std::cout << "Additional parameters:" << std::endl;
		std::cout << "-conv [input encoding][output encoding] convert encoding" << std::endl;
		std::cout << "    Encodings: utf8bom - UTF8 with BOM" << std::endl;
		std::cout << "               cp1251 - Windows-1251" << std::endl;
		std::cout << "-CyrLat - convert  cyrillic symbols to latin" << std::endl;
		std::cout << "-close - close after successful end" << std::endl;
		std::cout << " " << std::endl;
		std::cout << "Copyright (c) 2016 Kusii S.M." << std::endl;
		return;
	}

	size_t parIdx = 1;//skip run file
	std::cout << "File left = " << data[parIdx] << std::endl;
	g_inputCfg.sFileLeft = data[parIdx];
	parIdx++;
	std::cout << "File right = " << data[parIdx] << std::endl;
	g_inputCfg.sFileRight = data[parIdx];
	parIdx++;
	std::cout << "File out = " << data[parIdx] << std::endl;
	g_inputCfg.sFileOut = data[parIdx];
	parIdx++;
	while (parIdx < size){
		if (data[parIdx] == tag::sConvert) {
			parIdx++;
			if (parIdx + 2 < size) {
				auto getEncoding = [data](auto parIdx, auto& outEncoding) {
					if (data[parIdx] == tag::sUtf8Bom)
						outEncoding = eEncoding::utf8Bom;
					else if (data[parIdx] == tag::sCp1251)
						outEncoding = eEncoding::cp1251;
					else
						throw std::exception("Wrong parameters, unknown encoding.");
				};
				getEncoding(parIdx, g_inputCfg.convCfg.encFrom);
				parIdx++;
				getEncoding(parIdx, g_inputCfg.convCfg.encTo);
			}
			else{
				throw std::exception("Wrong parameters, input encodings.");
			}
		}
		else if (data[parIdx] == tag::sCyrLat) {
			g_inputCfg.convCfg.bTransformCyrToLat = true;
		}
		else if (data[parIdx] == tag::sClose) {
			g_inputCfg.bClose = true;
		}

		parIdx++;
	}
}

int main(size_t size, char **data)
{
	std::cout << "Make combine subtitre file" << std::endl;
	try
	{
		readInputData(size, data);

		cSubFile subFileLeft(g_inputCfg.convCfg);
		cSubFile subFileRight(g_inputCfg.convCfg);
		subFileLeft.readFromFile(g_inputCfg.sFileLeft);
		subFileRight.readFromFile(g_inputCfg.sFileRight);
		if (g_inputCfg.convCfg.bTransformCyrToLat) {
			subFileLeft.addSeparator();
		}
		subFileLeft.merge(subFileRight);
		subFileLeft.saveToFile(g_inputCfg.sFileOut);

		std::cout << "SUCCESS :)" << std::endl;
		if (g_inputCfg.bClose)
			return 0;
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

	system("pause");
    return 0;
}

