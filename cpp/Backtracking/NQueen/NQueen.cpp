#include <iostream>
#include <vector>
#include <string>

class NQueen {
    const int Size;
    std::vector<bool> col { };
    std::vector<bool> diag1 { };
    std::vector<bool> diag2 { };

public:
    NQueen(const int _Size) : Size { _Size }, col(Size, true), diag1(Size * 2, true), diag2(Size * 2, true) { }
    
    std::vector<std::vector<std::string>> answer { };
    
    void SolveNQueen(std::vector<std::string> &result) {
        if (static_cast<int>(result.size()) == Size) answer.push_back(result);
        std::string currentRow(Size, '.');                
        for(int j = 0; j < Size; ++j) {
            if (col[j]) {
                col[j] = false;
                if (diag1[Size + result.size() - j] && diag2[result.size() + j]) {
                    diag1[Size + result.size() - j] = false;
                    diag2[result.size() + j] = false;
                    currentRow[j] = 'Q';
                    result.push_back(currentRow);
                    SolveNQueen(result);
                    currentRow[j] = '.';
                    result.pop_back();
                    diag1[Size + result.size() - j] = true;
                    diag2[result.size() + j] = true;
                }
                
                col[j] = true;
            }
        }
    }
    
    void SolveNQueen() {
        std::vector<std::string> result { };
        SolveNQueen(result);
    }
};

std::ostream &operator<<(std::ostream &os, const std::vector<std::string> &resultlist) {
    os << "\t#" << std::string(resultlist.size(), '#') << "#\n";
    for(const auto &result: resultlist) {
        os << "\t#" << result << "#\n";
    }
    os << "\t#" << std::string(resultlist.size(), '#') << "#\n";
    return os;
}

std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<std::string>> &resultlist) {
    if (resultlist.empty()) {
        os << "All results:" << std::endl;
    } else {
        os << "All results for size: " << resultlist[0].size() << std::endl;
    }

    for(const auto &result: resultlist) {
        os << result;
    }
    return os;
}

int main(int, char *[]) {
    std::vector<int> testlist { 3, 4, 8};
    for(const auto &test: testlist) {
        NQueen nqueen { test };
        nqueen.SolveNQueen();
        std::cout << nqueen.answer << std::endl;
    }
    return 0;
}