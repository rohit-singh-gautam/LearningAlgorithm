///////////////////////////////////////
// ExpressionEvaluator.cpp
///////////////////////////////////////
//
// Grammar:
// Expression: E -> T + E | T - E | T
// Term: T -> V * T | V / T | V
// Value: V -> ( E ) | S
// Sign Number: S -> + S | - S | D
// Digit: D -> 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9

#include <string>
#include <stdexcept>
#include <vector>
#include <iostream>

void SkipWhiteSpace(std::string::const_iterator &it, const std::string::const_iterator &end) {
    while(it != end && (*it == ' ' || *it == '\t' || *it == '\r' || *it == '\n')) {
        it = std::next(it);
    }
}

int Digit(std::string::const_iterator &it, const std::string::const_iterator &end) {
    int result { 0 };
    while(it != end && *it >= '0' && *it <= '9') {
        result = result * 10 + *it - '0';
        it = std::next(it);
    }
    return result;
}

int SignedNumber(std::string::const_iterator &it, const std::string::const_iterator &end) {
    if (it == end) {
        throw std::runtime_error { "Expecting sign or number" };
    }

    int sign { 1 };
    if (*it == '-') {
        sign = -1;
        it = std::next(it);
    } else if (*it == '+') {
        it = std::next(it);
    }
    
    if (it == end || *it < '0' || *it > '9') {
        throw std::runtime_error { "Expecting number" };
    }

    return Digit(it, end) * sign;
}

int Expression(std::string::const_iterator &it, const std::string::const_iterator &end);

int Value(std::string::const_iterator &it, const std::string::const_iterator &end) {
    if (it == end) {
        throw std::runtime_error { "Expecting sign or number or expression" };
    }
    SkipWhiteSpace(it, end);
    if (*it == '(') {
        it = std::next(it);
        SkipWhiteSpace(it, end);
        auto result = Expression(it, end);
        SkipWhiteSpace(it, end);
        if (*it != ')') {
            throw std::runtime_error { "Expecting )" };
        }
        it = std::next(it);
        return result;
    }
    return SignedNumber(it, end);
}

int Term(std::string::const_iterator &it, const std::string::const_iterator &end) {
    int result = Value(it, end);
    SkipWhiteSpace(it, end);
    while(it != end) {
        auto ch = *it;
        if (ch != '*' && ch != '/') break;
        it = std::next(it);
        int rhs = Value(it, end);
        SkipWhiteSpace(it, end);
        if (ch == '*') result *= rhs;
        else if (ch == '/') result /= rhs;
    }
    return result;
}

int Expression(std::string::const_iterator &it, const std::string::const_iterator &end) {
    int result = Term(it, end);
    SkipWhiteSpace(it, end);
    while(it != end) {
        auto ch = *it;
        if (ch != '+' && ch != '-') break;
        it = std::next(it);
        int rhs = Term(it, end);
        SkipWhiteSpace(it, end);
        if (ch == '+') result += rhs;
        else if (ch == '-') result -= rhs;
    }
    return result;
}


int main(int, char *[]) {
    const std::vector<std::pair<std::string, int>> testlist {
        {"(1+1)", 2},
        {"1+1", 2},
        {" 1 + 1 ", 2},
        {"  (  1  +  1 ) ", 2},
        {"10 + 2*2", 14},
        {"2 * ( 10 + 3*(5))", 50},
        {"1", 1},
        {"223344", 223344},
        {"(20 + 20) * (30 + 30)", 2400},
        {"((20 + 20) * (30 + 30)) * 2", 4800}
    };
    
    for(const auto &[expr, expected]: testlist) {
        auto itr = std::begin(expr);
        auto result = Expression(itr, std::end(expr));
        std::cout << expr << " = " << result << ", expected: " << expected << std::endl;
        if (result != expected) {
            std::cout << "Test failed\n";
            break;
        }
    }

    return 0;
}