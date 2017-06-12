#pragma once
#include <string>

class cTime
{
public:
	cTime();
	cTime(const cTime& time);
	cTime(unsigned short hour, unsigned short minute, unsigned short second, unsigned short msecond);
	cTime(unsigned short hour, unsigned short minute, unsigned short second);
	~cTime();
	void set(const std::string& sLine);
	void clear();
	std::string cTime::getStr();
	bool operator==(const cTime& rTime) const;
	bool operator<(const cTime& rTime) const;
	cTime operator+(const unsigned short sec) const;
	cTime operator-(const unsigned short sec) const;
private:
	std::string to_string(unsigned short val);

	unsigned short _hour;
	unsigned short _minute;
	unsigned short _second;
	unsigned short _msecond;
};

