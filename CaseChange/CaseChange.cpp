#include "CaseChange.h"
#include <iostream>
#include <typeinfo>


void DisplayHexOne(const uint8_t val) {
    const char ch = val < 9 ? val + '0' : val - 10 + 'A';
    std::cout << ch;
}

void DisplayHex(auto value) {
    const auto valueptr = reinterpret_cast<uint8_t *>(&value);
    const auto max_size = sizeof(value);

    for(size_t index { 0 }; index < max_size; ++index) {
        const auto posvalue = valueptr[index];
        const auto posvaluelower = posvalue % 16;
        const auto posvalueupper = posvalue / 16;
        DisplayHexOne(posvalueupper);
        DisplayHexOne(posvaluelower);
    }
}


void TestRepeat() {
    constexpr const char ch {'a'};

    const auto val8 = CharHelper<1>::RepeatByte(ch);
    std::cout << "Value 8: ";
    DisplayHex(val8);
    std::cout << std::endl;

    const auto val16 = CharHelper<2>::RepeatByte(ch);
    std::cout << "Value 16: ";
    DisplayHex(val16);
    std::cout << std::endl;

    const auto val32 = CharHelper<4>::RepeatByte(ch);
    std::cout << "Value 32: ";
    DisplayHex(val32);
    std::cout << std::endl;

    const auto val64 = CharHelper<8>::RepeatByte(ch);
    std::cout << "Value 64: ";
    DisplayHex(val64);
    std::cout << std::endl;

    const auto val128 = CharHelper<16>::RepeatByte(ch);
    std::cout << "Value 128: ";
    DisplayHex(val128);
    std::cout << std::endl;
}

void TestToUpper() {
    std::cout << "Value 8: ";
    char ch {'a'};
    auto lower8 = CharHelper<1>::is_lower(ch);
    DisplayHex(lower8);
    std::cout << std::endl;

    std::cout << "Value 16: ";
    char ch2[] {"az"};
    const uint16_t ch16 {*reinterpret_cast<const uint16_t *>(ch2)};
    DisplayHex(ch16);
    std::cout << std::endl;
    auto lower16 = CharHelper<2>::is_lower(ch16);
    DisplayHex(lower16);
    std::cout << std::endl;
    CharHelper<2>::to_upper(ch2);
    std::cout << "Upper: " << ch2 << std::endl;

    std::cout << "Value 32: ";
    char ch4[] {"azAZ"};
    const uint32_t ch32 {*reinterpret_cast<const uint32_t *>(ch4)};
    DisplayHex(ch32);
    std::cout << std::endl;
    auto lower32 = CharHelper<4>::is_lower(ch32);
    DisplayHex(lower32);
    std::cout << std::endl;
    CharHelper<4>::to_upper(ch4);
    std::cout << "Upper: " << ch4 << std::endl;

    std::cout << "Value 64: ";
    char ch8_[] {"azAZ{}[s"};
    const uint64_t ch64 {*reinterpret_cast<const uint64_t *>(ch8_)};
    DisplayHex(ch64);
    std::cout << std::endl;
    auto lower64 = CharHelper<8>::is_lower(ch64);
    DisplayHex(lower64);
    std::cout << std::endl;
    CharHelper<8>::to_upper(ch8_);
    std::cout << "Upper: " << ch8_ << std::endl;

    std::cout << "Value 128: ";
    char ch16_[] {"azAZ{}[]bBxX .|s"};
    const __uint128_t ch128 {*reinterpret_cast<const __uint128_t *>(ch16_)};
    DisplayHex(ch128);
    std::cout << std::endl;
    auto lower128 = CharHelper<16>::is_lower(ch128);
    DisplayHex(lower128);
    std::cout << std::endl;
    CharHelper<16>::to_upper(ch16_);
    std::cout << "Upper: " << ch16_ << std::endl;
}

int main(int argc, char *argv[]) {
    TestToUpper();

    return 0;
}