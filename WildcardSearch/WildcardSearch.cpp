// WildcardSearch.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

using namespace std;

template <typename T>
std::ostream& operator<<(std::ostream& o, const std::vector<T>& arr) {
	const auto len = arr.size();
	size_t index = 0;
	for (; index < len - 1; index++) {
		o << arr[index] << " ";
	}

	o << arr.back();
	return o;
}

std::vector<int> createSearchMap(const string& wld) {
	const auto len = wld.size();
	std::vector<int> searchMap(len);
	searchMap[0] = 0;
	size_t wldindex = 0;

	//skip all initial wildcards
	while (wldindex < len && wld[wldindex] == '*') {
		searchMap[wldindex++] = wldindex;
		searchMap[wldindex] = wldindex;
	}
	size_t srchindex = wldindex;
	size_t textindex = wldindex + 1;

	while (textindex < len) {
		if (wld[textindex] == '*') {
			searchMap[textindex++] = textindex;
			if (textindex == len) break;
			searchMap[textindex] = textindex;
			srchindex = textindex;
			wldindex = textindex;
		}
		else {
			if (wld[srchindex] != wld[textindex]) {
				if (srchindex != wldindex) {
					srchindex = searchMap[wldindex];
					continue;
				}
			}
			else {
				srchindex++;
			}
			searchMap[textindex] = srchindex;
		}
		++textindex;
	}
	return searchMap;
}

// This cannot take care of '.'
bool searchStringUsingMap(const std::string& text, const std::string& wld) {
	const auto textlen = text.size();
	const auto wldlen = wld.size();
	const auto searchMap = createSearchMap(wld);
	size_t wldindex = 0;
	size_t textindex = 0;

	while (textindex < textlen) {
		if (text[textindex] != wld[wldindex]) {
			if (searchMap[wldindex] != wldindex) {
				wldindex = searchMap[wldindex];
				if (wldindex == wldlen) {
					// Wildcard at the end
					return true;
				}
			}
		}
		else {
			++wldindex;
			if (wldindex == wldlen) {
				// Only true if text is also completely red
				return textindex == textlen - 1;
			}
		}
		++textindex;
	}

	return false;
}


bool findmatch(const string &text, const string &wld) {
	size_t n = text.size();
	size_t m = wld.size();
	vector<vector<bool>> seq(n+1, vector<bool>(m+1, false));

	seq[0][0] = true;
	for (size_t i = 1; i <= m; i++) {
		if (wld[i - 1] == '*') {
			seq[0][i] = seq[0][i - 1];
		}
		else {
			break;
		}
	}

	for (size_t i = 1; i <= n; i++) {
		for (size_t j = 1; j <= m; j++) {
			if (text[i - 1] == wld[j - 1] || wld[j - 1] == '.') {
				seq[i][j] = seq[i - 1][j - 1];
			}
			else if (wld[j - 1] == '*') {
				seq[i][j] = seq[i - 1][j] || seq[i][j - 1];
			}
		}
	}
	
	return seq[n][m];
}


//NOT WORKING
bool findmatchfast(const string &text, const string &wld) {
	const size_t n = text.size();
	const size_t m = wld.size();

	size_t start = -1;

	size_t i = 0;
	size_t j = 0;

	while(j < n) {
		const char &v = text[j];
		if (wld[i] == '.' || wld[i] == v) {
			i++;
			j++;
		}
		else if (wld[i] == '*') {
			if (i == m - 1) {
				return true;
			}
			i++;
			start = i;
		}
		else if (start == -1) {
			return false;
		}
		else {
			i = start;
			j++;
		}
	}

	return i == m;
}



int main()
{
	const std::vector < std::pair<std::string, std::vector<std::string>>> tests = {
		{"This is a test for Apoorv Rohit Singh", {"*t.st*", "*ohit", "*ohit*"}},
		{"This is a test for abcabcd Apoorv Rohit Singh", {"*abcd*", "*ohit", "*ohit*"}}
	};

	for (const auto& test : tests) {
		std::cout << "TEXT: " << test.first << std::endl;

		for (const auto& srch : test.second) {
			const auto ret = searchStringUsingMap(test.first, srch) ? "true" : "false";
			std::cout << "\tRESULT: " << ret << "; SEARCH: " << srch << std::endl;
		}

		std::cout << std::endl;
	}
	
    return 0;
}

