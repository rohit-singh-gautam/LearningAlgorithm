#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <cstdint>
#include <ranges>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &data) {
    os << "{ ";
    for(const auto &entry: data) {
        os << entry << ' ';
    }
    return os << '}';
}

template <typename T>
void Display(std::ostream &os, const T &value) {
    if constexpr (std::same_as<T, std::string>) {
        for(const auto &ch: value) {
            if (ch >=32 && ch <= 127) {
                os << ch;
            } else {
                os << '#';
            }
        }
    } else {
        os << value;
    }
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &data) {
    os << '{';
    Display(os, data.first);
    os << ", ";
    Display(os, data.second);
    return os << '}';
}

template <typename KeyT, typename ValueT>
using MapType = std::map<KeyT, ValueT>;

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const MapType<T1, T2> &data) {
    os << "{ ";
    for(const auto &entry: data) {
        os << entry << ' ';
    }
    return os << '}';
}

template <typename OutType>
inline auto CreateLZWCompressDictionay() {
    MapType<std::string, OutType> dictionary { };
    for(OutType asciiCode { 0 }; asciiCode <= 255; ++asciiCode) {
        dictionary.emplace( std::string { static_cast<char>(asciiCode) }, asciiCode );
    }
    return dictionary;
}

template <typename InType>
inline auto CreateLZWUncompressDictionay() {
    MapType<InType, std::string> dictionary { };
    for(InType asciiCode { 0 }; asciiCode <= 255; ++asciiCode) {
        dictionary.emplace( asciiCode, std::string { static_cast<char>(asciiCode) } );
    }
    return dictionary;
}

template <typename OutType = uint32_t>
std::vector<OutType> LzwCompress(std::forward_iterator auto it, const std::forward_iterator auto end) {
    std::vector<OutType> compressedData { };
    if (it == end) return compressedData;
    auto dictionary = CreateLZWCompressDictionay<OutType>();
    auto currentPattern = std::string { static_cast<char>(*it) };
    it = std::next(it);
    while(it != end) {
        auto nextPattern = currentPattern + static_cast<char>(*it);
        if (dictionary.contains(nextPattern)) {
            currentPattern = nextPattern;
        } else {
            auto dictionarySize = dictionary.size();
            dictionary.emplace(nextPattern, dictionarySize);
            compressedData.push_back(dictionary.at(currentPattern));
            currentPattern = std::string { static_cast<char>(*it) };
        }
        it = std::next(it);
    }

    compressedData.push_back(dictionary.at(currentPattern));
    return compressedData;
}

template <typename OutType = uint32_t>
std::vector<OutType> LzwCompress(const std::ranges::range auto &data) {
    return LzwCompress<OutType>(std::begin(data), std::end(data));
}

auto LZWUncompress(std::forward_iterator auto it, const std::forward_iterator auto end) {
    using InType = std::decay_t<decltype(*it)>;
    if (it == end) return std::string { };
    auto dictionary = CreateLZWUncompressDictionay<InType>();

    auto previousData = dictionary[*it];
    std::string uncompressData = previousData;

    it = std::next(it);
    while(it != end) {
        auto dictionaryIterator = dictionary.find(*it);
        auto dictionarySize = dictionary.size();
        if (dictionaryIterator != std::end(dictionary)) {
            auto currentData = dictionaryIterator->second;
            uncompressData += currentData;
            dictionary.emplace(dictionarySize, previousData + currentData[0]);
            previousData = currentData;
        } else if (*it == dictionarySize) {
            previousData = previousData + previousData[0];
            uncompressData += previousData;
            dictionary.emplace(dictionarySize, previousData);
        } else {
            throw std::runtime_error { "Bad input compressed data" };
        }
        it = std::next(it);
    }


    return uncompressData;
}

auto LzwUncompress(const std::ranges::range auto &compressData) {
    return LZWUncompress(std::begin(compressData), std::end(compressData));
}

size_t LzwCompressSize(const std::ranges::range auto &compressData) {
    size_t size { 0 };
    for(const auto &value: compressData) {
        if (value <= 0x3f) ++size;
        else if (value <= 0x3fff) size += 2;
        else if (value <= 0x3fffff) size += 3;
        else if (value <= 0x3fffffff) size += 4;
        else throw std::runtime_error { "Too large to compress" };
    }
    return size;
}

bool test(const std::string &input) {
    auto compressed = LzwCompress(input);
    auto uncompressed = LzwUncompress(compressed);
    std::cout << "Input: " << input << std::endl;
    std::cout << "Compressed: " << compressed << std::endl;
    std::cout << "Uncompressed: " << uncompressed << std::endl;
    std::cout << "Input Size: " << input.size() << " Compressed Size: " << LzwCompressSize(compressed) << " Compressed vector Count: " << compressed.size() << std::endl;
    return input == uncompressed;
}

int main(int, char *[]) {
    const std::vector<std::string> testlist {
        "ABABABABABABABABABAB",
        "TOBEORNOTTOBEORTOBEORNOT",
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ",
        "AAAAAAAAAAAAAAAAAAAAAA",
        "123456789012345678901234567890",
        "",
        "A",
        "AA",
        "AAA",
        "ABA",
        "ABAB",
        "ABABA",
        "ABABAB",
        "ABABABA",
        "ABABABAB",
        "ABABABABA",
        "ABABABABAB",
        "ABABABABABA",
        "ABABABABABAB",
        "ABABABABABABA",
        "ABABABABABABAB",
        "ABABABABABABABA",
        "ABABABABABABABAB",
        "ABABABABABABABABA",
        "ABABABABABABABABAB",
        "ABABABABABABABABABA",
        "ABABABABABABABABABAB",
        "ABABABABABABABABABABA",
        "ABABABABABABABABABABAB",
        "ABABABABABABABABABABABA",
        "ABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABABABABABABAB",
        "ABABABABABABABABABABABABABABABABABABABABABABABABA",
        "ABABABABABABABABABABABABABABABABABABABABABABABABAB",
        "The quick brown fox jumps over the lazy dog",
        "Lorem ipsum dolor sit amet, consectetur adipiscing elit",
        "This is a test string for LZW compression algorithm",
        "This is a test that will make sure that proper huffman code is created. To create proper huffman code there must be sufficient large string, that must contain large number of character that is repeater several time. Huffman code consist of minimum number of bits for most repeated character and maximum number of bits for most repeated character. From normal look it is clear that space is very much repeated, other puncuation is also repeated a lot. So, space and puncuation must have minimum number of bits. Other character must have maximum number of bits.",
        "This is a test",
        "This is a test string",
        "This is a test string for",
        "This is a test string for LZW",
        "This is a test string for LZW compression",
        "This is a test string for LZW compression algorithm",
    };
    
    for(const auto &testentry: testlist) {
        auto result = test(testentry);
        if (!result) {
            std::cout << "Test failed" << std::endl;
            break;
        }
        std::cout << std::endl;
    }

    return 0;
}