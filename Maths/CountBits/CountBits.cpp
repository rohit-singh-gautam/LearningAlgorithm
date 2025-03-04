#include <iostream>
#include <cstdint>
#include <limits>

template <typename T, size_t PairCount, bool LSBZero>
consteval T Mask() {
    constexpr size_t totalBits = sizeof(T) * 8;
    if constexpr (PairCount >= totalBits) {
        if (LSBZero) {
            return 0;
        }
        return ~T(0);
    } else {
        T mask { 0 };
        T bit = LSBZero ? 0 : 1;
        size_t count { 0 };
        while(count < totalBits) {
            for(size_t index { 0 }; index < PairCount && count < totalBits; ++index, ++count) {
                mask |= bit << count;
            }
            bit = !bit;
        }
        return mask;
    }
}

template <typename T, T bits>
constexpr T CountBits(const T value) {
    static_assert(bits != 0);
    constexpr T totalbits = sizeof(T) * 8;
    if constexpr (bits > totalbits / 2) return value;
    else {
        T first = value & Mask<T, bits, false>();
        T second = value & Mask<T, bits, true>();
        second >>= bits;
        
        return CountBits<T, bits * 2>(first + second);
    }
}

template <typename T>
constexpr T CountBits(const T value) {
    return CountBits<T, 1>(value);
}

template <typename T>
constexpr T CountBits2(T value) {
    T count { 0 };
    while(value) {
        value &= (value - 1);
        ++count;
    }
    return count;
}

void DisplayBits(const auto value) {
    using ValueType = std::decay_t<decltype(value)>;
    std::cout << "0b";
    constexpr size_t totalbits = sizeof(value) * 8;
    ValueType currentBit = static_cast<ValueType>(1) << (totalbits - 1);
    for (size_t i = 0; i < totalbits; ++i) {
        std::cout << ((value & currentBit) ? "1" : "0");
        currentBit >>= 1;
    }
}

template <typename T, size_t PairCount, bool LSBZero>
void DisplayMask() {
    std::cout << "Mask<" << typeid(T).name() << ", " << PairCount << ", " << (LSBZero ? "true" : "false") << ">: ";
    T mask = Mask<T, PairCount, LSBZero>();
    DisplayBits(mask);
    std::cout << std::endl;
}

void TestBitMask() {
    DisplayMask<uint8_t, 1, false>();
    DisplayMask<uint8_t, 2, false>();
    DisplayMask<uint8_t, 4, false>();
    DisplayMask<uint8_t, 8, false>();
    DisplayMask<uint8_t, 1, true>();
    DisplayMask<uint8_t, 2, true>();
    DisplayMask<uint8_t, 4, true>();
    DisplayMask<uint8_t, 8, true>();
    DisplayMask<uint16_t, 1, false>();
    DisplayMask<uint16_t, 2, false>();
    DisplayMask<uint16_t, 4, false>();
    DisplayMask<uint16_t, 8, false>();
    DisplayMask<uint16_t, 16, false>();
    DisplayMask<uint16_t, 1, true>();
    DisplayMask<uint16_t, 2, true>();
    DisplayMask<uint16_t, 4, true>();
    DisplayMask<uint16_t, 8, true>();
    DisplayMask<uint16_t, 16, true>();
    DisplayMask<uint32_t, 1, false>();
    DisplayMask<uint32_t, 2, false>();
    DisplayMask<uint32_t, 4, false>();
    DisplayMask<uint32_t, 8, false>();
    DisplayMask<uint32_t, 16, false>();
    DisplayMask<uint32_t, 32, false>();
    DisplayMask<uint32_t, 1, true>();
    DisplayMask<uint32_t, 2, true>();
    DisplayMask<uint32_t, 4, true>();
    DisplayMask<uint32_t, 8, true>();
    DisplayMask<uint32_t, 16, true>();
    DisplayMask<uint32_t, 32, true>();
    DisplayMask<uint64_t, 1, false>();
    DisplayMask<uint64_t, 2, false>();
}

void TestCountBits(const auto value) {
    size_t ret1 = CountBits(value);
    size_t ret2 = CountBits2(value);
    if (ret1 == ret2) {
        std::cout << "Value: ";
        DisplayBits(value);
        std::cout << " has bits: " << ret1 << std::endl;
    } else {
        std::cout << "Test failed for value: ";
        DisplayBits(value);
        std::cout << " first return " << ret1 << " second return " << ret2 << std::endl;
        throw std::runtime_error { "Failed CountBits test" };
    }
}

void TestCountBitsAll() {
    try {
        TestCountBits(std::numeric_limits<uint64_t>::max());
        TestCountBits(std::numeric_limits<uint32_t>::max());
        TestCountBits(std::numeric_limits<uint16_t>::max());
        TestCountBits(std::numeric_limits<uint8_t>::max());
        TestCountBits(94572UL);
        TestCountBits(0UL);
        TestCountBits(1UL);
        TestCountBits(2UL);
        TestCountBits(3UL);
        TestCountBits(4UL);
        TestCountBits(5UL);
        TestCountBits(6UL);
        TestCountBits(7UL);
        TestCountBits(8UL);
        TestCountBits(9UL);
        TestCountBits(10UL);
        TestCountBits(1023U);
        TestCountBits(1024U);
        TestCountBits(1025U);
        TestCountBits(2047U);
        TestCountBits(2048U);
        TestCountBits(2049U);
        TestCountBits(4095U);
        TestCountBits(4096U);
        TestCountBits(4097U);
        TestCountBits(8191U);
        TestCountBits(8192U);
        TestCountBits(8193U);
        TestCountBits(16383UL);
        TestCountBits(16384UL);
        TestCountBits(16385UL);
        TestCountBits(32767UL);
        TestCountBits(32768UL);
        TestCountBits(32769UL);
        TestCountBits(65535UL);
        TestCountBits(65536UL);
        TestCountBits(65537UL);
        TestCountBits(131071UL);
        TestCountBits(131072UL);
        TestCountBits(131073UL);
        TestCountBits(262143UL);
        TestCountBits(262144UL);
        TestCountBits(262145UL);
        TestCountBits(524287UL);
        TestCountBits(524288UL);
        TestCountBits(524289UL);
        TestCountBits(1048575UL);
        TestCountBits(1048576UL);
        TestCountBits(1048577UL);
        TestCountBits(2097151UL);
        TestCountBits(2097152UL);
        TestCountBits(2097153UL);
        TestCountBits(4194303UL);
        TestCountBits(4194304UL);
        TestCountBits(4194305UL);
        TestCountBits(8388607UL);
        TestCountBits(8388608UL);
        TestCountBits(8388609UL);
        TestCountBits(16777215UL);
        TestCountBits(16777216UL);
        TestCountBits(16777217UL);
        TestCountBits(33554431UL);
        TestCountBits(33554432UL);
        TestCountBits(33554433UL);
        TestCountBits(67108863UL);
        TestCountBits(67108864UL);
        TestCountBits(67108865UL);
        TestCountBits(134217727UL);
        TestCountBits(134217728UL);
        TestCountBits(134217729UL);
        TestCountBits(268435455UL);
        TestCountBits(268435456UL);
        TestCountBits(268435457UL);
        TestCountBits(536870911UL);
        TestCountBits(536870912UL);
        TestCountBits(536870913UL);
        TestCountBits(1073741823UL);
        TestCountBits(1073741824UL);
        TestCountBits(1073741825UL);
        TestCountBits(2147483647UL);
        TestCountBits(2147483648UL);
        TestCountBits(2147483649UL);
    TestCountBits(4294967295UL);
    } catch(std::runtime_error &err) {
        std::cout << "Failed: " << err.what() << std::endl;
    }
}

int main(int, char *[]) {
    TestCountBitsAll();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}