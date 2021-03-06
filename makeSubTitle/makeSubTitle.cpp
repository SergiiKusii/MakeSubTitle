// makeSubTitle.cpp : Defines the entry point for the console application.
//
#include <iostream>
#include <string>
#include "cSubFile.h"

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
		std::cout << "Copyright (c) 2016 Kusii S.M." << std::endl;
	}
	else
	{
		try
		{
			data++; //skip run file
			std::cout << "File left = " << *data << std::endl;
			std::string sFileInLeft(*data);
			data++;
			std::cout << "File right = " << *data << std::endl;
			std::string sFileInRight(*data);
			data++;
			std::cout << "File out = " << *data << std::endl;
			std::string sFileOut(*data);

			cSubFile subFileLeft;
			cSubFile subFileRight;
			subFileLeft.readFromFile(sFileInLeft);
			subFileRight.readFromFile(sFileInRight);
			subFileLeft.merge(subFileRight);
			subFileLeft.saveToFile(sFileOut);

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

