#include "common.h"
#include "cSubFile.h"
#include <fstream>
#include <regex>
#include "Converter.h"

#define AUTHOR_NAME "Sergii Kusii"
#define FIRST_BLOC "0\r\n00:00:01,000 --> 00:00:05,000\r\nReleased by Sergii Kusii"

const std::string sSeparator = "-----------------------";

cSubFile::cSubFile(const convertCfg& convCfg)
	: m_convCfg(convCfg)
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

void cSubFile::convert(std::string& sLine)
{
	if (m_convCfg.bTransformCyrToLat){
		std::string sConertedLine;
		convertCyryllic(sLine, sConertedLine);
		sLine = sConertedLine;
	}

	if (m_convCfg.bConvert) {
		std::string sConertedLine;
		
		if (m_convCfg.encFrom == eEncoding::cp1251 && m_convCfg.encTo == eEncoding::utf8Bom) {
			cp1251_to_utf8(sLine.c_str(), sConertedLine);
		}
		else
			throw "Cannot convert, unknown convertor";

		sLine = sConertedLine;
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

void cSubFile::addBom(std::ofstream& File) {
	if (m_convCfg.bConvert){
		switch (m_convCfg.encTo)
		{
		case eEncoding::utf8Bom:
			File << bom::sUtf8;
			break;
		default:
			break;
		}
	}

}

void cSubFile::saveToFile(const std::string& sFileName)
{
	std::ofstream File(sFileName);

	if (!File)
		throw "ERR make out file: " + sFileName;

	addBom(File);

	for (size_t i = 0; i < _Fragments.size(); i++)
	{
		File << i << LINE_BREAK;
		File << _Fragments[i].getStr();
		File << LINE_BREAK;
	}

	File.close();
}

cFragment& cSubFile::operator[](size_t i)
{
	return _Fragments[i];
}

void cSubFile::addSeparator()
{
	for (auto& fragment : _Fragments){
		fragment.addText(sSeparator);
	}
}
