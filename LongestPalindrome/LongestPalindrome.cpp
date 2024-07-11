#include <iostream>
#include <vector>
#include <limits>

auto LongestPallindromeSubstring(const std::string &text) {
    size_t max_size = 1;
    size_t max_center = 0;

    std::vector<size_t> track(text.size(), 1 );

    size_t current_center { 1 };
    auto left {current_center - 1};
    auto right {current_center + 1};
    while(true) {

        while(left != std::numeric_limits<size_t>::max() && right < text.size()) {
            if (text[left] != text[right]) break;
            --left; ++right;
        }

        auto current_size {right - left - 1};
        track[current_center] = current_size;
        if (current_size > max_size) {
            max_center = current_center;
            max_size = current_size;
        }

        auto new_center { current_center + 1 };
        auto previous_size_loc { current_center - 1};
        auto previous_size { track[previous_size_loc] };
        while((previous_size - 1)/2 + new_center < right - 1) {
            --previous_size_loc;
            ++new_center;
            previous_size = track[previous_size_loc];
        }

        if (new_center >= text.size()) break;

        current_center = new_center;
        left = new_center * 2 - right;
    }


    return std::pair { max_center, max_size };
}


int main(int argc, char *argv[]) {
    // This works only for odd palindrom
    std::vector<std::string> values {
        "abaxabxbaxabb",
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