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

namespace bom {
	const std::string sUtf8 = "\xEF\xBB\0xBF";
}

void convertCyryllic(const std::string& sIn, std::string& sOut);
void cp1251_to_utf8(const char *in, std::string& sOut);
