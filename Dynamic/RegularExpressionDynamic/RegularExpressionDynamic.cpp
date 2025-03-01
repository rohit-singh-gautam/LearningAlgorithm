// RegularExpressionDynamic.cpp : Defines the entry point for the console application.
//

#include <type_traits>
#include <iostream>
#include <vector>
#include <string>


// +   x a * b c f
//   t f f f f f f
// x f t f f f f f
// a f f t t f f f // previous pattern char = current text char
// a f f f t f f f 
// a f f f t f f f
// b f f f f t f f
// c f f f f f t f
// f f f f f f f t

// +   x a *
//   t f f f
// x f t f t
// y f f f t

bool regexmatch(std::string text, std::string src) {
	const size_t n = text.size();
	const size_t m = src.size();

	std::vector<std::vector<bool>> s(n + 1, std::vector<bool>(m + 1, false));

	s[0][0] = true;

	for (size_t j = 1; j <= m; j++) {
		switch(src[j - 1]) {
		case '*':
			s[0][j] = s[0][j - 2];
			break;

		case '.':
			s[0][j] = s[0][j - 1];

		default:
			break;
		}
	}

	for (size_t i = 1; i <= n; i++) {
		for (size_t j = 1; j <= m; j++) {
			if (src[j - 1] == '.' || text[i - 1] == src[j - 1]) {
				s[i][j] = s[i - 1][j - 1];
			}
			else if (src[j - 1] == '*') {
				if (s[i][j - 2]) {
					s[i][j] = true;
				}
				else if (text[i - 1] == src[j - 2] || src[j-2] == '.') {
					s[i][j] = s[i - 1][j];
				}
			}
		}
	}

	return s[n][m];
}


int main()
{
	std::pair<std::string, std::string> search_list[] = {
		{"xyaaabcf", "xa*bcf"},
		{"xya", "xa*"},
		{"xy", "xa*"},
		{"xaaaabcf", "xa*bcf"},
		{"abcbcd", "a.*c.*d"},
		{"efwihfioghih35i", ".*"}
	};

	for (auto &value : search_list) {
		auto& [text, src] = value;
		const auto res = regexmatch(text, src);
		std::string res_str = res ? "true" : "false";

		std::cout << "Result: " << res_str << ", text: " << text << ", pattern: " << src << std::endl;

	}
    return 0;
}

