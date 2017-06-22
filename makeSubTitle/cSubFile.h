#pragma once
#include "cFragment.h"
#include <vector>
#include <string>
 
class cSubFile
{
public:
	cSubFile(const bool bConvCyryllic = false);
	void readFromFile(const std::string& sFileName);
	void merge(cSubFile& sFile);
	void saveToFile(const std::string& sFileName);
	size_t size();
	cFragment& operator[](size_t i);
	~cSubFile();

private:
	cSubFile(cSubFile& sFile);
	std::vector<cFragment> _Fragments;
	bool m_bConvCyryllic;

	void convert(std::string& sLine);
	void convertCyryllic(std::string& sLine);
};

