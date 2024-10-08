// KMPSearch.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <string>
#include <vector>
#include <array>

template <typename char_type>
constexpr auto CreateKMPMap(const char_type *srch, const size_t size) {
	std::vector<size_t> map { 0 };

	if (size == 1) return map;

	size_t srchindex = 0;
	size_t textindex = 1;

	while (textindex < size) {
		if (srch[srchindex] == srch[textindex]) {
			++srchindex;
			map[textindex] = srchindex;
			++textindex;
		}
		else {
			if (srchindex != 0) {
				srchindex = map[srchindex - 1];
				continue;
			}
			else {
				map[textindex] = 0;
				++textindex;
			}
		}
	}

	return map;
}

template <typename char_type>
constexpr bool findstr(const char_type *text, const size_t text_size, const char_type *srch, const size_t srch_size) {
	if (srch_size > text_size) return false;
	if (srch_size == text_size) {
		return std::equal(std::begin(text), std::end(text), std::begin(srch));
	}
	auto kmpmap = CreateKMPMap(srch, srch_size);
	
	size_t srchindex = 0;
	size_t textindex = 1;

	while (textindex < text_size) {
		if (text[textindex] == srch[srchindex]) {
			++srchindex;
			if (srchindex == srch_size) return true;
		}
		else {
			if (srchindex != 0) {
				srchindex = kmpmap[srchindex - 1];
				continue;
			}
		}
		++textindex;
	}
	
	return false;
}

template <typename char_type, size_t text_size, size_t srch_size>
constexpr bool findstr(const char_type(&text)[text_size + 1], const char_type(&srch)[srch_size + 1]) {
	return findstr(text, text_size, srch, srch_size);
}

std::vector<size_t> CreateKMPMap(const std::string& srch) {
	const auto len = srch.size();
	std::vector<size_t> kmap(len);
	kmap[0] = 0;
	size_t textindex = 1;
	size_t srchindex = 0;


	// abcabcd
	// 0001230
	// Alway a position ahead of match is stored, in case of no match it is 0
	// For back search we always look for previous srchindex position (srchindex - 1)
	while (textindex < len) {
		if (srch[textindex] != srch[srchindex]) {
			if (srchindex != 0) {
				srchindex = kmap[srchindex - 1];
				continue;
			}
		}
		else {
			srchindex++;
		}
		kmap[textindex] = srchindex;
		textindex++;
	}

	return kmap;
}

bool findstr(const std::string& text, const std::string& srch) {
	const auto kmap = CreateKMPMap(srch);
	const auto textlen = text.size();
	const auto srchlen = srch.size();
	size_t textindex = 0;
	size_t srchindex = 0;

	while (textindex < textlen) {
		if (text[textindex] != srch[srchindex]) {
			if (srchindex != 0) {
				srchindex = kmap[srchindex - 1];
				continue;
			}
		}
		else {
			srchindex++;
			if (srchindex == srchlen) {
				return true;
			}
		}
		textindex++;
	}

	return false;
}

void test() {
	const std::vector<std::pair<std::string, std::vector<std::string>>> tests{
		{"This is a test for Apoorv Rohit Singh", {"for Apojn", "Rohit", "This", "Singh", "test"} },
		{"abcabce aslxp abc abcabc abcabcdabcd aslkmbn", {"abcabcdabcd", "abcabcd", "abcabcabcd", "abcabce"} }
	};

	for (const auto& test : tests) {
		const auto text = test.first;
		std::cout << "TEXT: " << text << std::endl;

		for (const auto& srch : test.second) {
			const auto ret = findstr(text, srch) ? "true" : "false";
			std::cout << "\tRESULT: " << ret << "; SEARCH: " << srch << std::endl;
		}
		std::cout << std::endl;
	}
}

template <typename char_type, size_t N, size_t M, typename ...ARGS>
void test_const_one(const char_type (&text)[N], const char_type (&srch)[M], const ARGS&... args) {
	std::cout << "TEXT: " << text << std::endl;
	const auto ret = findstr(text, srch) ? "true" : "false";
	std::cout << "\tRESULT: " << ret << "; SEARCH: " << srch << std::endl;

	if constexpr (sizeof...(args) >= 1) {
		test_const_one(text, args...);
	}
}

void test_const() {
	test_const_one("This is a test for Apoorv Rohit Singh", "for Apojn", "Rohit", "This", "Singh", "test");
	test_const_one("abcabce aslxp abc abcabc abcabcdabcd aslkmbn", "abcabcdabcd", "abcabcd", "abcabcabcd", "abcabce");
}


int main()
{
	test();
	test_const();
	return 0;
}
