#include <cmath>
#include <cstdio>
#include <ios>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

// { "key": "value"}
// Bool, Number, String, Null, Member, Array, Object
// "true"
// [1, 4, "Test"]
//
// JSON: Bool | Number | String | Array | Object
// Bool : True | false
// Number: Integer
// String: ".*"
// Array: [ JSON, JSON, ... ]
// Member: String ":" JSON
// Object: {Member}

// Ignoring Escapes

void skipws(const std::string &value, size_t &index);
bool parsenumber(const std::string &value, size_t &index);
bool parsestring(const std::string &value, size_t &index);
bool parseMember(const std::string &value, size_t &index);

bool parsejson(const std::string &value, size_t &index) {
    skipws(value, index);
    switch(value[index]) {
        case 'T':
            if (value.substr(index, 4) != "TRUE") return false;
            index += 4;
            break;
        case 'F':
            if (value.substr(index, 5) != "FALSE") return false;
            index += 5;
            break;

        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9':
            if (!parsenumber(value, index)) return false;
            break;
            
        case '"':
            if (!parsestring(value, index)) return false;
            break;
        
        case '[':
            ++index; 
            while(true) {
                skipws(value, index);
                if (!parsejson(value, index)) return false;
                skipws(value, index);
                // "[1, 2, 3, 4, 5]"
                if (value[index] != ',') {
                    if (value[index] != ']') return false;
                    ++index;
                    break;
                }
                ++index;
            }
            break;
        case '{':
            ++index;
            while(true) {
                skipws(value, index);
                if (!parseMember(value, index)) return false;
                skipws(value, index);
                if (value[index] != ',') {
                    if (value[index] != '}') return false;
                    ++index;
                    break;
                }
                ++index;
            }
            break;
            
    }
    skipws(value, index);
    return true;
}

bool parseMember(const std::string &value, size_t &index) {
    skipws(value, index);
    if (!parsestring(value, index)) return false;
    skipws(value, index);
    if (value[index] != ':' ) return false;
    ++index;
    skipws(value, index);
    if (!parsejson(value, index)) return false;
    skipws(value, index);
    return true;
}

bool parsestring(const std::string &value, size_t &index) {
    if (value[index] != '"') return false;
    ++index;
    while(value[index] != '"') {
        ++index;
        if (index == value.size()) return false;
    }
    ++index;
    skipws(value, index);
    return true;
}

void skipws(const std::string &value, size_t &index) {
    if (index >= value.size()) return;
    auto ch = value[index];
    while(ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r') {
        ++index;
        if (index >= value.size()) break;
        ch = value[index];
    }
}

bool parsenumber(const std::string &value, size_t &index) {
    skipws(value, index);
    while(index < value.size() && value[index] >= '0' && value[index] <= '9') {
        ++index;
    }
    skipws(value, index);
    if (index >= value.size()) return true;
    if (value[index] != ']' && value[index] != '}' && value[index] != ',') return false;
    skipws(value, index);
    return true;
}

bool parsejson(const std::string &value) {
    size_t index { 0 };
    if (!parsejson(value, index)) return false;
    skipws(value, index);
    return index == value.size();
}

int main() {
    const std::vector<std::pair<std::string, bool>> test_cases {
        {"{ \"Test\": \"Value\"}", true},
        {"{ \"Test\": 4955 }", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\"}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5]}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"}, \"Test8\": { \"Test9\": \"Value9\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"}, \"Test8\": { \"Test9\": \"Value9\"}, \"Test10\": { \"Test11\": \"Value11\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"}, \"Test8\": { \"Test9\": \"Value9\"}, \"Test10\": { \"Test11\": \"Value11\"}, \"Test12\": { \"Test13\": \"Value13\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5", false},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5]", false},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5]}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}", false},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"", false},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"}}", true},
        {"{ \"Test\": 4955, \"Test2\": \"Value\", \"Test3\": [1, 2, 3, 4, 5], \"Test4\": { \"Test5\": \"Value5\"}, \"Test6\": { \"Test7\": \"Value7\"}, \"Test8\": { \"Test9\": \"Value9\"", false},
        {"TRUE", true},
        {"1204", true},
        {"\"Rohit\"", true},
        {"[1, 2, 3, 4, 5]", true},
        {"[1, 2, 4", false},
        {"[1, 2, 3, 4, 5][1, 2, 4,", false}
    };
    
    for(auto &[test_case, expected]: test_cases) {
        const auto result = parsejson(test_case);
        std::cout << "JSON: " << test_case << ", is valid: " << result << ", expected: " << expected << std::endl;
        if (result != expected) {
            std::cout << "Test case failed: " << test_case << std::endl;
            break;
        }
    }

    return 0;
}