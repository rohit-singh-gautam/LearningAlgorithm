#include <iostream>
#include <queue>
#include <filesystem>

struct node {
    char c;
    int frequency;
    node *left;
    node *right;

    constexpr node(char c, int frequency) : c(c), frequency(frequency), left(nullptr), right(nullptr) { }

    constexpr node(node *left, node *right)
        : c('0'), frequency(left->frequency + right->frequency), left(left), right(right) { }

    constexpr node(node &&rhs) : c(rhs.c), frequency(rhs.frequency), left(rhs.left), right(rhs.right) {
        rhs.left = nullptr;
        rhs.right = nullptr;
    }

    node(const node &rhs) = delete;
    node &operator=(node &&rhs) = delete;
    node &operator=(const node &rhs) = delete;

    ~node() {
        delete(left); left = nullptr;
        delete(right); right = nullptr;
    }

    void traverse(std::string code) {
        if (left == nullptr) {
            std::cout << c << ":" << frequency << ": " << code << std::endl;
        } else {
            code.push_back('0');
            left->traverse(code);
            code.pop_back();
            code.push_back('1');
            right->traverse(code);
            code.pop_back();
        }
    }

    void traverse() {
        std::string code { };
        traverse(code);
    }

    constexpr bool operator<(const node &rhs) { return frequency < rhs.frequency; }
    constexpr bool operator>(const node &rhs) { return frequency > rhs.frequency; }
};


void CreateHuffmanCode(const std::string &str) {
    int frequency[256] = {0};
    std::fill(frequency, frequency + 256, 0);

    for(auto ch: str) {
        ++frequency[int(ch)];
    }

    auto cmp = [](const node *const lhs, const node *const rhs) { return lhs->frequency > rhs->frequency; };
    std::priority_queue<node *, std::vector<node *>, decltype(cmp)> priority(cmp);
    for(int ch = 0; ch < 256; ++ch) {
        if (frequency[ch]) {
            node *nd = new node((char)ch, frequency[ch]);
            priority.push(nd);
        }
    }

    srand(static_cast<unsigned int>(time(nullptr)));
    while(priority.size() != 1) {
        node *left;
        node *right;
        if (rand() > RAND_MAX / 2) {
            left = priority.top();
            priority.pop();
            right = priority.top();
            priority.pop();
        } else {
            right = priority.top();
            priority.pop();
            left = priority.top();
            priority.pop();
        }
        node *nd = new node(left, right);
        priority.push(nd);
    }

    priority.top()->traverse();
}

void test() {
    std::vector<std::string> testlist {
        "This is a test that will make sure that proper huffman code is created. To create proper huffman code there must be sufficient large string, that must contain large number of character that is repeater several time. Huffman code consist of minimum number of bits for most repeated character and maximum number of bits for most repeated character. From normal look it is clear that space is very much repeated, other puncuation is also repeated a lot. So, space and puncuation must have minimum number of bits. Other character must have maximum number of bits. This is a test that will make sure that proper huffman code is created. To create proper huffman code there must be sufficient large string, that must contain large number of character that is repeater several time. Huffman code consist of minimum number of bits for most repeated character and maximum number of bits for most repeated character. From normal look it is clear that space is very much repeated, other puncuation is also repeated a lot. So, space and puncuation must have minimum number of bits. Other character must have maximum number of bits.",
        "This is a test"
    };

    for(auto &str: testlist) {
        std::cout << "Test: " << str << std::endl;
        CreateHuffmanCode(str);
        std::cout << std::endl;
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::filesystem::path path { argv[0] };
        std::cout << path.filename() << ": <string>" << std::endl;
        test();
    } else {
        CreateHuffmanCode(argv[1]);
    }
    return EXIT_SUCCESS;
}




