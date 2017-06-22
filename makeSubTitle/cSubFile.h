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
	void addSeparator();
	size_t size();
	cFragment& operator[](size_t i);
	~cSubFile() = default;

private:
	cSubFile(cSubFile& sFile);
	std::vector<cFragment> _Fragments;
	bool m_bConvCyryllic;

	void convert(std::string& sLine);
};

