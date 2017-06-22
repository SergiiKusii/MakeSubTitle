#include "common.h"
#include "cSubFile.h"
#include <fstream>
#include <regex>

#define AUTHOR_NAME "Sergii Kusii"
#define FIRST_BLOC "0\r\n00:00:01,000 --> 00:00:05,000\r\nReleased by Sergii Kusii"

std::vector<std::pair<char, std::string>> g_cyryllicLatinMap = { 
	{'à', "a"},
	{'À', "A"},
	{ 'á', "b" },
	{ 'Á', "B" },
	{ 'â', "v" },
	{ 'Â', "V" },
	{ 'ã', "g" },
	{ 'Ã', "G" },
	{ 'ä', "d" },
	{ 'Ä', "D" },
	{ 'å', "e" },
	{ 'Å', "E" },
	{ '¸', "zh" },
	{ '¨', "Zh" },
	{ 'æ', "zh" },
	{ 'Æ', "Zh" },
	{ 'ç', "zh" },
	{ 'Ç', "Zh" },
	{ 'è', "zh" },
	{ 'È', "Zh" },
	{ 'é', "zh" },
	{ 'É', "Zh" },
	{ 'ê', "zh" },
	{ 'Ê', "Zh" },
	{ 'ë', "zh" },
	{ 'Ë', "Zh" },
	{ 'ì', "zh" },
	{ 'Ì', "Zh" },
	{ 'í', "zh" },
	{ 'Í', "Zh" },
	{ 'î', "zh" },
	{ 'Î', "Zh" },
	{ 'ï', "zh" },
	{ 'Ï', "Zh" },
	{ 'ð', "zh" },
	{ 'Ð', "Zh" },
	{ 'ñ', "zh" },
	{ 'Ñ', "Zh" },
	{ 'ò', "zh" },
	{ 'Ò', "Zh" },
	{ 'ó', "zh" },
	{ 'Ó', "Zh" },
	{ 'ô', "zh" },
	{ 'Ô', "Zh" },
	{ 'õ', "zh" },
	{ 'Õ', "Zh" },
	{ 'ö', "zh" },
	{ 'Ö', "Zh" },
	{ '÷', "zh" },
	{ '×', "Zh" },
	{ 'ø', "zh" },
	{ 'Ø', "Zh" },
	{ 'ù', "zh" },
	{ 'Ù', "Zh" },
	{ 'ú', "zh" },
	{ 'Ú', "Zh" },
	{ 'û', "zh" },
	{ 'Û', "Zh" },
	{ 'ü', "zh" },
	{ 'Ü', "Zh" },
	{ 'ý', "zh" },
	{ 'Ý', "Zh" },
	{ 'þ', "zh" },
	{ 'Þ', "Zh" },
	{ 'ÿ', "zh" },
	{ 'ß', "Zh" },
};

cSubFile::cSubFile(const bool bConvCyryllic) 
	: m_bConvCyryllic(bConvCyryllic)
{
	//TODO add author bloc
}

/*
2
00:00 : 55, 422 --> 00:00 : 59, 256
There's nothing to tell.
It's just some guy I work with.
*/
void cSubFile::readFromFile(const std::string& sFileName)
{
	std::ifstream File(sFileName);

	if (!File)
		throw "ERR: no file: " + sFileName;

	cFragment Fragment;
	std::string sLine;
	std::regex regStartFragment("[0123456789]{1,3}");
	std::regex regTime("[0123456789]{2}:[0123456789]{2}:[0123456789]{2}[0123456789,]{0,4} --> [0123456789]{2}:[0123456789]{2}:[0123456789]{2}[0123456789,]{0,4}");
	bool isFragment = false;

	while (File) {
		std::getline(File, sLine);

		if (isFragment)
		{
			if (sLine.empty())
			{
				isFragment = false;
				Fragment.check();
				_Fragments.push_back(Fragment);
				Fragment.clear();
			}
			else
			{
				if (std::regex_match(sLine, regTime))
					Fragment.addTime(sLine);
				else {
					convert(sLine);
					Fragment.addText(sLine);
				}	
			}
		}
		else if (std::regex_match(sLine, regStartFragment))
			isFragment = true;
	}

	File.close(); 
}

void cSubFile::convertCyryllic(std::string& sLine)
{


}

void cSubFile::convert(std::string& sLine)
{
	if (m_bConvCyryllic){
		convertCyryllic(sLine);
	}
}

size_t cSubFile::size()
{
	return _Fragments.size();
}

void cSubFile::merge(cSubFile& subFileRight)
{
	size_t iCurFrag = 0;
	size_t iSeconFrag = 0;

	while (iSeconFrag < subFileRight.size() || iCurFrag < _Fragments.size())
	{
		if (iSeconFrag >= subFileRight.size())
			break;
		else if (iCurFrag >= _Fragments.size())
		{
			_Fragments.push_back(subFileRight[iSeconFrag]);
			iSeconFrag++;
		}
		else if (_Fragments[iCurFrag] == subFileRight[iSeconFrag])
		{
			_Fragments[iCurFrag].addText(subFileRight[iSeconFrag]);
			iCurFrag++;
			iSeconFrag++;
		}
		else if (_Fragments[iCurFrag] < subFileRight[iSeconFrag])
			iCurFrag++;
		else
			iSeconFrag++;
	}
}

void cSubFile::saveToFile(const std::string& sFileName)
{
	std::ofstream File(sFileName);

	if (!File)
		throw "ERR make out file: " + sFileName;

//	std::string str;

	for (size_t i = 0; i < _Fragments.size(); i++)
	{
		File << i << LINE_BREAK;
		File << _Fragments[i].getStr();
		File << LINE_BREAK;

		//str += std::to_string(i);
		//str += LINE_BREAK;
		//str += _Fragments[i].getStr();
		//str += LINE_BREAK;
	}

//	File << str;
	File.close();
}

cFragment& cSubFile::operator[](size_t i)
{
	return _Fragments[i];
}

cSubFile::~cSubFile(){}
