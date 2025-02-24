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
#include <iterator>
#include <ranges>

template <std::forward_iterator It>
class ExpressionEvaluator {
    It it;
    const It end;

    constexpr void SkipWhiteSpace() {
        while(it != end && (*it == ' ' || *it == '\t' || *it == '\r' || *it == '\n')) {
            it = std::next(it);
        }
    }

    constexpr auto Integer() {
        int result { 0 };
        while(it != end && *it >= '0' && *it <= '9') {
            result = result * 10 + *it - '0';
            it = std::next(it);
        }
        return result;
    }

    constexpr double Float() {
        auto integer = Integer();
        if (it == end || *it != '.') return integer;
        it = std::next(it);
        auto decimal = Integer();
        double result { 0 };
        while(decimal) {
            result += decimal % 10;
            result /= 10;
            decimal /= 10;
        }
        result += integer;
        return result;
    }

    constexpr auto SignedNumber() {
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
    
        return Float() * sign;
    }

    constexpr auto Value() {
        if (it == end) {
            throw std::runtime_error { "Expecting sign or number or expression" };
        }
        SkipWhiteSpace();
        if (*it == '(') {
            it = std::next(it);
            SkipWhiteSpace();
            auto result = Expression();
            SkipWhiteSpace();
            if (*it != ')') {
                throw std::runtime_error { "Expecting )" };
            }
            it = std::next(it);
            return result;
        }
        return SignedNumber();
    }

    constexpr auto Term() {
        auto result = Value();
        SkipWhiteSpace();
        while(it != end) {
            auto ch = *it;
            if (ch != '*' && ch != '/') break;
            it = std::next(it);
            auto rhs = Value();
            SkipWhiteSpace();
            if (ch == '*') result *= rhs;
            else if (ch == '/') result /= rhs;
        }
        return result;
    }
    
    constexpr double Expression() {
        auto result = Term();
        SkipWhiteSpace();
        while(it != end) {
            auto ch = *it;
            if (ch != '+' && ch != '-') break;
            it = std::next(it);
            auto rhs = Term();
            SkipWhiteSpace();
            if (ch == '+') result += rhs;
            else if (ch == '-') result -= rhs;
        }
        return result;
    }

public:
    constexpr ExpressionEvaluator(It begin, It end): it { begin }, end { end } {}
    double Evaluate() {
        return Expression();
    }
}; // ExpressionEvaluator

template <std::ranges::range range>
constexpr auto MakeEvaluator(const range &r) { return ExpressionEvaluator { std::begin(r), { std::end(r) } }; }

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
        auto evaluator = MakeEvaluator(expr);
        auto result = evaluator.Evaluate();
        std::cout << expr << " = " << result << ", expected: " << expected << std::endl;
        if (result != expected) {
            std::cout << "Test failed\n";
            break;
        }
    }

    return 0;
}