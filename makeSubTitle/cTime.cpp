#include "stdafx.h"
#include "cTime.h"


cTime::cTime()
{
	_hour = 0;
	_minute = 0;
	_second = 0;
	_msecond = 0;
}

cTime::cTime(unsigned short hour, unsigned short minute, unsigned short second, unsigned short msecond)
{
	_hour = hour;
	_minute = minute;
	_second = second;
	_msecond = msecond;
}

cTime::cTime(unsigned short hour, unsigned short minute, unsigned short second)
{
	_hour = hour;
	_minute = minute;
	_second = second;
	_msecond = 0;
}

cTime::cTime(const cTime& time)
{
	_hour = time._hour;
	_minute = time._minute;
	_second = time._second;
	_msecond = time._msecond;
}

void cTime::clear()
{
	_hour = 0;
	_minute = 0;
	_second = 0;
	_msecond = 0;
}

//00:29:08
void cTime::set(const std::string& sLine)
{
	auto iCurPos = 0;
	_hour = std::stoi(sLine.substr(iCurPos, 2));
	iCurPos += 3;
	_minute = std::stoi(sLine.substr(iCurPos, 2));
	iCurPos += 3;
	_second = std::stoi(sLine.substr(iCurPos, 2));
}

std::string cTime::getStr()
{
	std::string str(to_string(_hour));
	str.push_back(':');
	str += to_string(_minute);
	str.push_back(':');
	str += to_string(_second);
	return str;
}

std::string cTime::to_string(unsigned short val)
{
	std::string str(std::to_string(val));
	if (str.size() == 1)
		return "0" + str;
	else
		return str;
}

cTime::~cTime(){}

bool cTime::operator==(const cTime& rTime) const
{
	return _hour == rTime._hour && _minute == rTime._minute && _second == rTime._second && _msecond == rTime._msecond;
}

bool cTime::operator<(const cTime& rTime) const
{
	return _hour < rTime._hour 
		|| _hour == rTime._hour && _minute < rTime._minute 
		|| _hour == rTime._hour && _minute == rTime._minute && _second < rTime._second 
		|| _hour == rTime._hour && _minute == rTime._minute && _second == rTime._second && _msecond < rTime._msecond;
}

cTime cTime::operator+(const unsigned short sec) const
{
	unsigned short addSec = 0;
	unsigned short addMin = 0;
	unsigned short addHour = 0;
	
	addSec = sec + _second + _minute*60 + _hour*60*60;

	addHour = addSec / (60 * 60);
	addSec -= addHour * 60 * 60;
	addMin = addSec / 60;
	addSec -= addMin * 60;
	
	return cTime(addHour, addMin, addSec);
}

cTime cTime::operator-(const unsigned short sec) const
{
	unsigned short addSec = 0;
	unsigned short addMin = 0;
	unsigned short addHour = 0;

	addSec = (_second + _minute * 60 + _hour * 60 * 60) < sec ? 0 : _second + _minute * 60 + _hour * 60 * 60 - sec;

	addHour = addSec / (60 * 60);
	addSec -= addHour * 60 * 60;
	addMin = addSec / 60;
	addSec -= addMin * 60;

	return cTime(addHour, addMin, addSec);
}