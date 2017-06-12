#include "common.h"
#include "cFragment.h"


cFragment::cFragment()
{
	_isTimeSet = false;
}

cFragment::cFragment(const cFragment& frag)
{
	_timeStart = frag._timeStart;
	_timeEnd = frag._timeEnd;

	for (size_t i = 0; i < frag._txtBlock.size(); i++)
		_txtBlock.push_back(frag._txtBlock[i]);

}

void cFragment::check()
{
	if (!_isTimeSet)
		throw "ERR: Time no set";
}
void cFragment::clear()
{
	_isTimeSet = false;
	_timeStart.clear();
	_timeEnd.clear();
	_txtBlock.clear();
}

//00:29:08,146 --> 00:29:09,613
void cFragment::addTime(const std::string& sLine)
{
	auto iTimeLen = 8;
	_timeStart.set(sLine.substr(0, iTimeLen));
	auto iCurPos = sLine.find(ARROW);
	if (iCurPos == std::string::npos)
		throw "ERR: Bad time str: " + sLine;

	iCurPos += strlen(ARROW) + 1;
	_timeEnd.set(sLine.substr(iCurPos, iTimeLen));

	_isTimeSet = true;
}

void cFragment::addText(const std::string& sLine)
{
	_txtBlock.push_back(sLine);
}

void cFragment::addText(const cFragment& frag)
{
	for (size_t i = 0; i < frag._txtBlock.size(); i++)
		_txtBlock.push_back(frag._txtBlock[i]);
}

std::string cFragment::getStr()
{
	std::string str(_timeStart.getStr());
	str.push_back(' ');
	str += ARROW;
	str.push_back(' ');
	str += _timeEnd.getStr();
	str += LINE_BREAK;

	for (size_t i = 0; i < _txtBlock.size(); i++)
	{
		str += _txtBlock[i];
		str += LINE_BREAK;
	}
	return str;
}

bool cFragment::operator<(const cFragment& frag) const
{
	return  _timeStart < frag._timeStart;// && _timeEnd < frag._timeEnd;
}

bool cFragment::operator==(const cFragment& frag) const
{
	return (_timeStart == frag._timeStart || _timeStart == frag._timeStart + 1 || _timeStart == frag._timeStart - 1) 
		 && (_timeEnd == frag._timeEnd || _timeEnd == frag._timeEnd + 1 || _timeEnd == frag._timeEnd - 1);
}

cFragment::~cFragment(){}
