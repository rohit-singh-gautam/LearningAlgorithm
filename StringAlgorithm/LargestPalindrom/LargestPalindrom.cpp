// LargestPalindrom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// PalindromAlgorithm.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>
#include <tuple>
#include <iostream>

// NOT TESTED, int was changed to size_t that was not tested

auto longestpaliondrom1(std::string text) {
	auto n = text.size();
	std::vector<decltype(n)> len(n);
	decltype(n) max = 1;
	decltype(n) maxpos = 0;

	decltype(n) right = 1;
	// ababaxabaxabadsxg
	for (decltype(n) i = 0; i < n;) {
		while (2 * i - right >= 0 && right < n && text[2 * i - right] == text[right]) {
			right++;
		}

		len[i] = (right - i) * 2 - 1;

		if (len[i] > max) {
			max = len[i];
			maxpos = i;
		}

		decltype(n) k;
		for (k = i + 1; k < right && len[2 * i - k] + k < right; k++) {
			len[k] = len[2 * i - k];
		}
		i = k;
	}

	return max;
}

auto longestpaliondrom(std::string text) {
	size_t n = text.size();
	std::vector<size_t> len(n);
	size_t j;
	size_t max = 1;
	size_t maxpos = 0;
	j = 1;
	for (size_t i = 0; i < n;) {
		while (i >= j && i + j < n && text[i - j] == text[i + j]) {
			j++;
		}
		j--;

		len[i] = 2 * j + 1;

		if (len[i] > max) {
			max = len[i];
			maxpos = i;
		}

		if (j >= 1) {
			size_t k = 1;
			while (k <= j && len[i - k] < (j - k) * 2 + 1) {
				len[i + k] = len[i - k];
				k++;
			}
			i += k;
			j = k;
		}
		else {
			i++;
			j = 1;
		}
	}
	auto start_max = maxpos - (max / 2);

	return std::tie(start_max, max);
}

auto longestpaliondromeven(std::string text) {
	size_t n = text.size();
	std::vector<size_t> len(n - 1);
	size_t j;
	size_t max = 0;
	size_t maxpos = -1;
	for (int i = 0; i < n - 1;) {
		j = 0;
		while (i - j >= 0 && i + j + 1 < n && text[i - j] == text[i + j + 1]) {
			j++;
		}

		len[i] = 2 * j;

		if (len[i] > max) {
			max = len[i];
			maxpos = i + 1;
		}

		if (j >= 2) {
			int k = 1;
			while (k < j && len[i - k] < (j - k) * 2) {
				len[i + k] = len[i - k];
				k++;
			}
			k--;
			i += k;
		}
		else {
			i++;
		}
	}

	return max;
}

int main()
{
	std::string text = "ababaxabaxabadsxg";
	std::string text1 = "abbaxxabbasdt";
	std::string text2 = "asdtabbaxxabba";

	//int val = longestpaliondromeven(text2);
	auto [start, size] = longestpaliondrom(text);
	std::string largest_palidrom = text.substr(start, size);
	std::cout << "Largest palindrom: " << largest_palidrom << std::endl;

	return 0;
}

