#pragma once
#include "cTime.h"
#include <vector>
#include <string>

class cFragment
{
public:
	cFragment();
	cFragment(const cFragment& frag);
	void addTime(const std::string& sLine);
	void addText(const std::string& sLine);
	void addText(const cFragment& frag);
	void check();
	void clear();
	std::string getStr();
	bool operator<(const cFragment& frag) const;
	bool operator==(const cFragment& frag) const;
	~cFragment();
private:
	cTime _timeStart;
	cTime _timeEnd;
	std::vector<std::string> _txtBlock;
	bool _isTimeSet;
};

