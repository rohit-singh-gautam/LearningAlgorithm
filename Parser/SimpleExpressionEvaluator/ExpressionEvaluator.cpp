///////////////////////////////////////
// ExpressionEvaluator.cpp
///////////////////////////////////////
//
// Grammar:
// Expression: E -> T + E | T - E | T
// Term: T -> V * T | V / T | V
// Value: V -> ( E ) | S
// Sign Number: S -> + F | - F | F
// Float: F -> I "." I
// I: I -> D I | D
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

int Integer(std::string::const_iterator &it, const std::string::const_iterator &end) {
    int result { 0 };
    while(it != end && *it >= '0' && *it <= '9') {
        result = result * 10 + *it - '0';
        it = std::next(it);
    }
    return result;
}

double Float(std::string::const_iterator &it, const std::string::const_iterator &end) {
    auto integer = Integer(it, end);
    if (it == end || *it != '.') return integer;
    it = std::next(it);
    auto decimal = Integer(it, end);
    double result { 0 };
    while(decimal) {
        result += decimal % 10;
        result /= 10;
        decimal /= 10;
    }
    result += integer;
    return result;
}

double SignedNumber(std::string::const_iterator &it, const std::string::const_iterator &end) {
    if (it == end) {
        throw std::runtime_error { "Expecting sign or number" };
    }

    double sign { 1 };
    if (*it == '-') {
        sign = -1;
        it = std::next(it);
    } else if (*it == '+') {
        it = std::next(it);
    }
    
    if (it == end || *it < '0' || *it > '9') {
        throw std::runtime_error { "Expecting number" };
    }

    return Float(it, end) * sign;
}

double Expression(std::string::const_iterator &it, const std::string::const_iterator &end);

double Value(std::string::const_iterator &it, const std::string::const_iterator &end) {
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

double Term(std::string::const_iterator &it, const std::string::const_iterator &end) {
    double result = Value(it, end);
    SkipWhiteSpace(it, end);
    while(it != end) {
        auto ch = *it;
        if (ch != '*' && ch != '/') break;
        it = std::next(it);
        double rhs = Value(it, end);
        SkipWhiteSpace(it, end);
        if (ch == '*') result *= rhs;
        else if (ch == '/') result /= rhs;
    }
    return result;
}

double Expression(std::string::const_iterator &it, const std::string::const_iterator &end) {
    double result = Term(it, end);
    SkipWhiteSpace(it, end);
    while(it != end) {
        auto ch = *it;
        if (ch != '+' && ch != '-') break;
        it = std::next(it);
        double rhs = Term(it, end);
        SkipWhiteSpace(it, end);
        if (ch == '+') result += rhs;
        else if (ch == '-') result -= rhs;
    }
    return result;
}


int main(int, char *[]) {
    const std::vector<std::pair<std::string, double>> testlist {
        {"223344.987654321", 223344.987654321},
        {"(1+1.1)", 2.1},
        {"1+1", 2},
        {" 1 + 1 ", 2},
        {"  (  1  +  1 ) ", 2},
        {"10 + 2*2", 14},
        {"2 * ( 10 + 3*(5))", 50},
        {"1", 1},
        {"223344", 223344},
        {"(20 + 20) * (30 + 30)", 2400},
        {"((20 + 20) * (30 + 30)) * 2.1", 5040},
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