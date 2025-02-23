#include <iostream>
#include <queue>

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

    void traverse(const std::string &code = "") {
        if (left == nullptr) {
            std::cout << c << ":" << frequency << ": " << code << std::endl;
        } else {
            left->traverse(code + '0');
            right->traverse(code + '1');
        }
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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "huffmancode: <string>" << std::endl;
    } else {
        CreateHuffmanCode(argv[1]);
    }
    return EXIT_SUCCESS;
}




