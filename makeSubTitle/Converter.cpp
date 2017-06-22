#include "Converter.h"
#include <vector>
#include <algorithm>

std::vector<std::pair<char, std::string>> g_cyryllicLatinMap = {
	{ '�', "a" },
	{ '�', "A" },
	{ '�', "b" },
	{ '�', "B" },
	{ '�', "v" },
	{ '�', "V" },
	{ '�', "g" },
	{ '�', "G" },
	{ '�', "d" },
	{ '�', "D" },
	{ '�', "e" },
	{ '�', "E" },
	{ '�', "zh" },
	{ '�', "Zh" },
	{ '�', "zh" },
	{ '�', "Zh" },
	{ '�', "z" },
	{ '�', "Z" },
	{ '�', "i" },
	{ '�', "I" },
	{ '�', "y" },
	{ '�', "Y" },
	{ '�', "k" },
	{ '�', "K" },
	{ '�', "l" },
	{ '�', "L" },
	{ '�', "m" },
	{ '�', "M" },
	{ '�', "n" },
	{ '�', "N" },
	{ '�', "o" },
	{ '�', "O" },
	{ '�', "p" },
	{ '�', "P" },
	{ '�', "r" },
	{ '�', "R" },
	{ '�', "s" },
	{ '�', "S" },
	{ '�', "t" },
	{ '�', "T" },
	{ '�', "u" },
	{ '�', "U" },
	{ '�', "f" },
	{ '�', "F" },
	{ '�', "kh" },
	{ '�', "Kh" },
	{ '�', "c" },
	{ '�', "C" },
	{ '�', "ch" },
	{ '�', "Ch" },
	{ '�', "sh" },
	{ '�', "Sh" },
	{ '�', "shch" },
	{ '�', "Shch" },
	{ '�', "`" },
	{ '�', "`" },
	{ '�', "y" },
	{ '�', "Y" },
	{ '�', "`" },
	{ '�', "`" },
	{ '�', "e" },
	{ '�', "E" },
	{ '�', "yu" },
	{ '�', "Yu" },
	{ '�', "ya" },
	{ '�', "Ya" }, };

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