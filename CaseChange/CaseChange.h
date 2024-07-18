#include <cstdint>
#include <iostream>

template <int typesize>
class SizeToType {
public:
    using TYPE = void;
    static constexpr int bytes = typesize;
};

template <>
class SizeToType<1> {
public:
    using TYPE = uint8_t;
    static constexpr int bytes = 1;
};

template <>
class SizeToType<2> {
public:
    using TYPE = uint16_t;
    static constexpr int bytes = 2;
};

template <>
class SizeToType<4> {
public:
    using TYPE = uint32_t;
    static constexpr int bytes = 4;
};

template <>
class SizeToType<8> {
public:
    using TYPE = uint64_t;
    static constexpr int bytes = 8;
};

template <>
class SizeToType<16> {
public:
    using TYPE = __uint128_t;
};

template <int typesize>
class CharHelper : public SizeToType<typesize> {
public:
    using TYPE = SizeToType<typesize>::TYPE;
   
    static constexpr TYPE RepeatByte(const uint8_t u8ch) {
        if constexpr (typesize == 1) {
            return u8ch;
        } else {
            TYPE sourcech = CharHelper<typesize/2>::RepeatByte(u8ch);
            TYPE leftshift =  typesize * 4;
            return sourcech << leftshift | sourcech;
        }
    }

    static constexpr TYPE RepeatByte(const char ch) {
        const auto u8ch = static_cast<uint8_t>(ch);
        return RepeatByte(u8ch);
    }

    static constexpr TYPE Get_AboveEqual_128() {
        constexpr uint8_t value = 0x80;
        return RepeatByte(value);
    }

    static constexpr TYPE Get_Above_z() {
        constexpr uint8_t value = 0x80 - 'z' - 1;
        return RepeatByte(value);
    }

    static constexpr TYPE Get_AboveEqual_a() {
        constexpr uint8_t value = 0x80 - 'a';
        return RepeatByte(value);
    }

    static constexpr TYPE Get_AboveEqual_A() {
        constexpr uint8_t value = 0x80 - 'A';
        return RepeatByte(value);
    }

    static constexpr TYPE Get_Above_Z() {
        constexpr uint8_t value = 0x80 - 'Z' - 1;
        return RepeatByte(value);
    }

    static constexpr TYPE is_lower(const TYPE value) {
        const TYPE AboveEqual128 { static_cast<TYPE>(~value & Get_AboveEqual_128()) };
        const TYPE ASCIIBits { static_cast<TYPE>(value & ~Get_AboveEqual_128()) };
        const TYPE Above_z { static_cast<TYPE>(~(ASCIIBits + Get_Above_z()) & Get_AboveEqual_128()) };
        const TYPE AboveEqual_a { static_cast<TYPE>(ASCIIBits + Get_AboveEqual_a() & Get_AboveEqual_128()) };
        const TYPE result = static_cast<TYPE>(AboveEqual128 & Above_z & AboveEqual_a);
        constexpr TYPE shiftright { 2 };
        return result >> shiftright;
    }

    static constexpr TYPE is_upper(const TYPE value) {
        const TYPE AboveEqual128 { static_cast<TYPE>(~value & Get_AboveEqual_128()) };
        const TYPE ASCIIBits { static_cast<TYPE>(value & ~Get_AboveEqual_128()) };
        const TYPE Above_Z { static_cast<TYPE>(~(ASCIIBits + Get_Above_Z()) & Get_AboveEqual_128()) };
        const TYPE AboveEqual_A { static_cast<TYPE>(ASCIIBits + Get_AboveEqual_A() & Get_AboveEqual_128()) };
        const TYPE result = static_cast<TYPE>(AboveEqual128 & Above_Z & AboveEqual_A);
        constexpr TYPE shiftright { 2 };
        return result >> shiftright;
    }

    static constexpr void to_upper(char *ch) {
        TYPE *chptr { reinterpret_cast<TYPE *>(ch) };
        TYPE islower = is_lower(*chptr);
        *chptr -= islower;
    }

    static constexpr void to_lower(char *ch) {
        TYPE *chptr { reinterpret_cast<TYPE *>(ch) };
        TYPE isupper = is_upper(*chptr);
        *chptr += isupper;
    }
};

constexpr void to_upper(char *ch, size_t size) {
    while(size >= 16) {
        CharHelper<16>::to_upper(ch);
        ch += 16;
        size -= 16;
    }

    if (size >= 8) {
        CharHelper<8>::to_upper(ch);
        ch += 8;
        size -= 8;
    }

    if (size >= 4) {
        CharHelper<4>::to_upper(ch);
        ch += 4;
        size -= 4;
    }

    if (size >= 2) {
        CharHelper<2>::to_upper(ch);
        ch += 2;
        size -= 2;
    }

    if (size) {
        CharHelper<2>::to_upper(ch);
    }
}

constexpr void to_upper(std::string &text) {
    to_upper(text.data(), text.size());
}

constexpr void to_lower(char *ch, size_t size) {
    while(size >= 16) {
        CharHelper<16>::to_lower(ch);
        ch += 16;
        size -= 16;
    }

    if (size >= 8) {
        CharHelper<8>::to_lower(ch);
        ch += 8;
        size -= 8;
    }

    if (size >= 4) {
        CharHelper<4>::to_lower(ch);
        ch += 4;
        size -= 4;
    }

    if (size >= 2) {
        CharHelper<2>::to_lower(ch);
        ch += 2;
        size -= 2;
    }

    if (size) {
        CharHelper<2>::to_lower(ch);
    }
}

constexpr void to_lower(std::string &text) {
    to_lower(text.data(), text.size());
}
