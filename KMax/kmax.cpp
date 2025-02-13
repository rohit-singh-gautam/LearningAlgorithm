#include "kmax.h"
#include <iostream>

template <typename NumType>
std::ostream &operator<<(std::ostream &os, const std::vector<NumType> &values) {
    os << "{ ";
    for(auto &value: values) {
        os << value << ' ';
    }
    os << '}';
    return os;
}

template <typename NumType>
std::ostream &operator<<(std::ostream &os, const std::pair<std::vector<NumType>, size_t> &value) {
    os << value.first << '[' << value.second << ']';
    return os;
}

template <typename comparator, typename NumType> 
bool CheckResult(std::vector<NumType> &values, std::vector<NumType> &result) {
    std::sort(std::begin(values), std::end(values), comparator {});
    std::sort(std::begin(result), std::end(result), comparator {});

    for(size_t index { 0 }; index < result.size(); ++index) {
        if (values[index] != result[index]) return false;
    }
    return true;
}

template <typename comparator, typename NumType>
void test(std::vector<std::pair<std::vector<NumType>, size_t>> &tests) {
    for(auto &test: tests) {
        std::cout << test << ": ";
        auto result = GetTopK<comparator>(test.first, test.second);
        std::cout << result << " - ";
        auto testresult = CheckResult<comparator>(test.first, result);
        if (testresult) std::cout << "Pass";
        else std::cout << "Fail";
        std::cout << '\n';
    }
}

int main(int const, char const *[]) {
    std::vector<std::pair<std::vector<int>, size_t>> tests {
        {{35, 12, 24, 55, 10}, 3},
        {{10}, 1},
        {{10, 20}, 2},
        {{10, 20}, 1},
        {{20, 10}, 1},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 5},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 2},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 10},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 1},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 5},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 4},
        {{30, 40, 10, 20, 90, 50, 11, 24, 55, 66, 77, 39, 24, 54}, 8},
    };

    test<std::less<>>(tests);
    test<std::greater<>>(tests);

    return 0;
}