#pragma once
#include <string>

enum class eEncoding {
	utf8Bom,
	cp1251,
};

struct convertCfg
{
	bool bConvert = false;
	eEncoding encFrom;
	eEncoding encTo;

	bool bTransformCyrToLat = false;
};

void convertCyryllic(const std::string& sIn, std::string& sOut);
