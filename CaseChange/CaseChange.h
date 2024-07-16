#include <cstdint>
#include <iostream>


template <typename CHARTYPE>
constexpr auto RepeatByte8(CHARTYPE ch) {
    static_assert(std::is_same_v<CHARTYPE, char> || std::is_same_v<CHARTYPE, uint8_t>);
    const auto u8ch = static_cast<uint8_t>(ch);
    return u8ch;
}

template <typename CHARTYPE>
constexpr auto RepeatByte16(CHARTYPE ch) {
    const auto u8ch = RepeatByte8(ch);
    const uint16_t u16ch = static_cast<uint16_t>(u8ch) << static_cast<uint16_t>(8) | static_cast<uint16_t>(u8ch);
    return u16ch;
}

template <typename CHARTYPE>
constexpr auto RepeatByte32(CHARTYPE ch) {
    const auto u16ch = RepeatByte16(ch);
    const uint32_t u32ch = static_cast<uint32_t>(u16ch) << static_cast<uint32_t>(16) | static_cast<uint32_t>(u16ch);
    return u32ch;
}

template <typename CHARTYPE>
constexpr auto RepeatByte64(CHARTYPE ch) {
    const auto u32ch = RepeatByte32(ch);
    const uint64_t u64ch = static_cast<uint64_t>(u32ch) << static_cast<uint64_t>(32) | static_cast<uint64_t>(u32ch);
    return u64ch;
}

template <typename CHARTYPE>
constexpr auto RepeatByte128(CHARTYPE ch) {
    const auto u64ch = RepeatByte64(ch);
    const __uint128_t u128ch = static_cast<__uint128_t>(u64ch) << static_cast<__uint128_t>(64) | static_cast<__uint128_t>(u64ch);
    return u128ch;
}

constexpr uint8_t Const_Above_127_8 { 0x80 };
constexpr uint8_t Const_Above_z_8 { Const_Above_127_8 - 'z' - 1};
constexpr uint8_t Const_Above_a_8 { Const_Above_127_8 - 'a'};
constexpr uint8_t ToUpperDiff_8 { 'a' - 'A' };

constexpr uint16_t Const_Above_127_16 { RepeatByte16(Const_Above_127_8) };
constexpr uint16_t Const_Above_z_16 { RepeatByte16(Const_Above_z_8) };
constexpr uint16_t Const_Above_a_16 { RepeatByte16(Const_Above_a_8) };
constexpr uint16_t ToUpperDiff_16 { RepeatByte16(ToUpperDiff_8) };

constexpr uint32_t Const_Above_127_32 { RepeatByte32(Const_Above_127_8) };
constexpr uint32_t Const_Above_z_32 { RepeatByte32(Const_Above_z_8) };
constexpr uint32_t Const_Above_a_32 { RepeatByte32(Const_Above_a_8) };
constexpr uint32_t ToUpperDiff_32 { RepeatByte32(ToUpperDiff_8) };

constexpr uint64_t Const_Above_127_64 { RepeatByte64(Const_Above_127_8) };
constexpr uint64_t Const_Above_z_64 { RepeatByte64(Const_Above_z_8) };
constexpr uint64_t Const_Above_a_64 { RepeatByte64(Const_Above_a_8) };
constexpr uint64_t ToUpperDiff_64 { RepeatByte64(ToUpperDiff_8) };

constexpr __uint128_t Const_Above_127_128 { RepeatByte128(Const_Above_127_8) };
constexpr __uint128_t Const_Above_z_128 { RepeatByte128(Const_Above_z_8) };
constexpr __uint128_t Const_Above_a_128 { RepeatByte128(Const_Above_a_8) };
constexpr __uint128_t ToUpperDiff_128 { RepeatByte128(ToUpperDiff_8) };

constexpr uint8_t is_lower(const uint8_t value) {
    const uint8_t Above_127_8 { static_cast<uint8_t>(~value & Const_Above_127_8) };
    const uint8_t lower_value { static_cast<uint8_t>(value & ~Const_Above_127_8) };
    const uint8_t Above_z_8 { static_cast<uint8_t>(~(lower_value + Const_Above_z_8) & Const_Above_127_8) };
    const uint8_t Above_a_8 { static_cast<uint8_t>((lower_value + Const_Above_a_8) & Const_Above_127_8) };
    
    const uint8_t result = Above_127_8 & Above_z_8 & Above_a_8;
    return result >> 2;
}

constexpr uint8_t is_lower(const char value) {
    return is_lower(static_cast<uint8_t>(value));
}

constexpr uint16_t is_lower(const uint16_t value) {
    const uint16_t Above_127_16 { static_cast<uint16_t>(~value & Const_Above_127_16) };
    const uint16_t lower_value { static_cast<uint16_t>(value & ~Const_Above_127_16) };
    const uint16_t Above_z_16 { static_cast<uint16_t>(~(lower_value + Const_Above_z_16) & Const_Above_127_16) };
    const uint16_t Above_a_16 { static_cast<uint16_t>((lower_value + Const_Above_a_16) & Const_Above_127_16) };
    
    const uint16_t result = Above_127_16 & Above_z_16 & Above_a_16;
    return result >> 2;
}

constexpr uint32_t is_lower(const uint32_t value) {
    const uint32_t Above_127_32 { ~value & Const_Above_127_32 };
    const uint32_t lower_value { value & ~Const_Above_127_32 };
    const uint32_t Above_z_32 { ~(lower_value + Const_Above_z_32) & Const_Above_127_32 };
    const uint32_t Above_a_32 { (lower_value + Const_Above_a_32) & Const_Above_127_32 };
    
    const uint32_t result =  Above_127_32 & Above_z_32 & Above_a_32;
    return result >> 2;
}

constexpr uint64_t is_lower(const uint64_t value) {
    const uint64_t Above_127_64 { ~value & Const_Above_127_64 };
    const uint64_t lower_value { value & ~Const_Above_127_64 };
    const uint64_t Above_z_64 { ~(lower_value + Const_Above_z_64) & Const_Above_127_64 };
    const uint64_t Above_a_64 { (lower_value + Const_Above_a_64) & Const_Above_127_64 };
    
    const uint64_t result = Above_127_64 & Above_z_64 & Above_a_64;
    return result >> 2;
}

constexpr __uint128_t is_lower(const __uint128_t value) {
    const __uint128_t Above_127_128 { ~value & Const_Above_127_128 };
    const __uint128_t lower_value { value & ~Const_Above_127_128 };
    const __uint128_t Above_z_128 { ~(lower_value + Const_Above_z_128) & Const_Above_127_128 };
    const __uint128_t Above_a_128 { (lower_value + Const_Above_a_128) & Const_Above_127_128 };
    
    const __uint128_t result = Above_127_128 & Above_z_128 & Above_a_128;
    return result >> 2;
}

template <size_t count, bool left = false>
constexpr void tolower(char *ch) {
    if constexpr (count == 1) {
        auto islower = is_lower(*ch);
        *ch -= ToUpperDiff_8 & islower;
    } else if constexpr (count == 2) {
        auto chptr = reinterpret_cast<uint16_t *>(ch);
        auto islower = is_lower(*chptr);
        *chptr -= ToUpperDiff_16 & islower;
    } else if constexpr (count == 3) {
        if constexpr (left) {
            tolower<1>(ch);
            tolower<2>(ch + 1);
        } else {
            tolower<2>(ch);
            tolower<1>(ch + 2);
        }
    } else if constexpr (count == 4) {
        auto chptr = reinterpret_cast<uint32_t *>(ch);
        auto islower = is_lower(*chptr);
        *chptr -= ToUpperDiff_32 & islower;
    } else if constexpr (count == 8) {
        auto chptr = reinterpret_cast<uint64_t *>(ch);
        auto islower = is_lower(*chptr);
        *chptr -= ToUpperDiff_64 & islower;
    } else {
        static_assert(count == 16);
        auto chptr = reinterpret_cast<__uint128_t *>(ch);
        auto islower = is_lower(*chptr);
        *chptr -= ToUpperDiff_128 & islower;
    }
}
