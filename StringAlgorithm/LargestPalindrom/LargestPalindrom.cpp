// LargestPalindrom.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// PalindromAlgorithm.cpp : Defines the entry point for the console application.
//

#include <string>
#include <vector>
#include <tuple>
#include <iostream>
#include <limits>

// Best working code
auto LongestPallindromeSubstring(const std::string &text) {
    size_t max_size = 1;
    size_t max_center = 0;

    std::vector<size_t> track(text.size() * 2 - 1, 0 );
    track[0] = 1;

    size_t current_center { 1 };
    auto left {current_center - 1};
    auto right {current_center};
    while(true) {

        while(left != std::numeric_limits<size_t>::max() && right < text.size()) {
            if (text[left] != text[right]) break;
            --left; ++right;
        }

        auto current_size {right - left - 1};
        auto track_index { (current_center * 2) - !(current_size % 2) };
        track[track_index] = current_size;
        if (current_size > max_size) {
            max_center = current_center - !(current_size % 2);
            max_size = current_size;
        }

        auto new_track_index { track_index + 1 };
        auto previous_size_loc { track_index - 1};
        auto previous_size { track[previous_size_loc] };
        while((previous_size - 1 + new_track_index)/2 < right - 1) {
            track[new_track_index] = track[previous_size_loc];
            --previous_size_loc;
            ++new_track_index;
            previous_size = track[previous_size_loc];
        }

        if ((new_track_index + 1)/2 >= text.size()) break;

        current_center = (new_track_index + 1)/2;
        left = new_track_index - right;
    }

    return std::pair { max_center, max_size };
}



int main()
{
	std::vector<std::string> values {
        "bb",
        "abaxabxbaxabb",
		"ababaxabaxabadsxg",
		"abbaxxabbasdt",
		"asdtabbaxxabba",
        "a",
        "aa",
        "aaa",
        "aaaaa",
        "aaaaaaaaaaaaaaaaaaaaaa"
    };

    for(auto value: values) {
        auto [center, size] = LongestPallindromeSubstring(value);
        auto start = center - (size - 1) / 2;
        auto substr = value.substr(start, size);
        std::cout << "Original: (" << value.size() << ") " << value << ", Largest: (" << size << ") " << substr << ", Start: " << start << std::endl;
    }

	return 0;
}

