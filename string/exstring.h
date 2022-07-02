#ifndef __EXSTRING__
#define __EXSTRING__
#include <string>
#include <vector>
#include "exsort.h"
namespace exalg {
	std::vector<int> KMPfail(std::string pattern) {
		std::vector<int> pmatchTable(pattern.length());
		for (int i = 1, j = 0; i < pattern.length(); i++) {
			while (j > 0 && pattern[i] != pattern[j])
				j = pmatchTable[j - 1];
			if (pattern[i] == pattern[j])
				pmatchTable[i] = ++j;
		}
		return pmatchTable;
	}
	std::vector<int> KMP(std::string text, std::string pattern) {
		std::vector<int> pos;
		std::vector<int> pmatchTable = KMPfail(pattern);
		for (int i = 0, j = 0; i < text.length(); i++) {
			while (j > 0 && text[i] != pattern[j])
				j = pmatchTable[j - 1];
			if (text[i] == pattern[j]) {
				if (j == pattern.length() - 1) {
					pos.push_back(i - pattern.length() + 1);
					j = pmatchTable[j];
				}
				else j++;
			}
		}
		return pos;
	}

	std::vector<int> GetSA_Naive(std::string text) { //O(n^2 * logn)

	}

	std::vector<int> GetSA_ManberMyers(std::string text) { //O(nlogn)

	}

	std::vector<int> GetSuffixArray(std::string text) {
		//SA-IS Algorithm Here...
	}
}
#endif
