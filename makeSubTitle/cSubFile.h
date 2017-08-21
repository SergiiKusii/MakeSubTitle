#pragma once
#include "cFragment.h"
#include <vector>
#include <string>
#include "Converter.h"
 
class cSubFile
{
public:
	cSubFile(const convertCfg& convCfg);
	void readFromFile(const std::string& sFileName);
	void merge(cSubFile& sFile);
	void saveToFile(const std::string& sFileName);
	void addSeparator();
	size_t size();
	cFragment& operator[](size_t i);
	~cSubFile() = default;

private:
	cSubFile(cSubFile& sFile);
	std::vector<cFragment> _Fragments;
	convertCfg m_convCfg;

	void convert(std::string& sLine);
	void addBom(std::ofstream& File);
};

