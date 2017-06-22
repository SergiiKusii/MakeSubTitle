#include "Converter.h"
#include <vector>
#include <algorithm>

std::vector<std::pair<char, std::string>> g_cyryllicLatinMap = {
	{ 'à', "a" },
	{ 'À', "A" },
	{ 'á', "b" },
	{ 'Á', "B" },
	{ 'â', "v" },
	{ 'Â', "V" },
	{ 'ã', "g" },
	{ 'Ã', "G" },
	{ 'ä', "d" },
	{ 'Ä', "D" },
	{ 'å', "e" },
	{ 'Å', "E" },
	{ '¸', "zh" },
	{ '¨', "Zh" },
	{ 'æ', "zh" },
	{ 'Æ', "Zh" },
	{ 'ç', "z" },
	{ 'Ç', "Z" },
	{ 'è', "i" },
	{ 'È', "I" },
	{ 'é', "y" },
	{ 'É', "Y" },
	{ 'ê', "k" },
	{ 'Ê', "K" },
	{ 'ë', "l" },
	{ 'Ë', "L" },
	{ 'ì', "m" },
	{ 'Ì', "M" },
	{ 'í', "n" },
	{ 'Í', "N" },
	{ 'î', "o" },
	{ 'Î', "O" },
	{ 'ï', "p" },
	{ 'Ï', "P" },
	{ 'ð', "r" },
	{ 'Ð', "R" },
	{ 'ñ', "s" },
	{ 'Ñ', "S" },
	{ 'ò', "t" },
	{ 'Ò', "T" },
	{ 'ó', "u" },
	{ 'Ó', "U" },
	{ 'ô', "f" },
	{ 'Ô', "F" },
	{ 'õ', "kh" },
	{ 'Õ', "Kh" },
	{ 'ö', "c" },
	{ 'Ö', "C" },
	{ '÷', "ch" },
	{ '×', "Ch" },
	{ 'ø', "sh" },
	{ 'Ø', "Sh" },
	{ 'ù', "shch" },
	{ 'Ù', "Shch" },
	{ 'ú', "`" },
	{ 'Ú', "`" },
	{ 'û', "y" },
	{ 'Û', "Y" },
	{ 'ü', "`" },
	{ 'Ü', "`" },
	{ 'ý', "e" },
	{ 'Ý', "E" },
	{ 'þ', "yu" },
	{ 'Þ', "Yu" },
	{ 'ÿ', "ya" },
	{ 'ß', "Ya" }, };

void convertCyryllic(const std::string& sIn, std::string& sOut)
{
	sOut.clear();
	for (auto it = sIn.begin(); it != sIn.end(); it++) {
		auto copied = false;
		for (auto& pair : g_cyryllicLatinMap){
			if (*it == pair.first) {
				sOut += pair.second;
				copied = true;
				break;
			}
		}
		if (!copied)
			sOut += *it;
	} 
}