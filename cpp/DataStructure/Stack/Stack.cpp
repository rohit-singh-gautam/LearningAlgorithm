#include <iostream>
#include <vector>

template <typename ValueT>
class Stack {
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &s);
    ValueT *store { };
    size_t size;
    size_t top { 0 };

    void Resize() {
        size_t newsize = size * 2;
        ValueT *newStore = new ValueT[newsize];
        for (size_t i = 0; i < top; ++i) {
            newStore[i] = std::move(store[i]);
        }
        delete[] store;
        store = newStore;
        size = newsize;
    }
public:
    Stack(size_t size) : store { new ValueT[size]}, size { size }, top { 0 } { }
    Stack(const Stack &) = delete;

    ~Stack() {
        delete[] store;
    }

    Stack & operator=(const Stack &) = delete;

    template <typename T>
    void Push(const T &v) {
        if (top == size) {
            Resize();
        }
        store[top++] = v;
    }

    template <typename T>
    void Push(T &&v) {
        if (top == size) {
            Resize();
        }
        store[top++] = std::forward(v);
    }
    ValueT &Top() {
        return store[top - 1];
    }
    bool Pop() {
        if (top == 0) {
            return false;
        }
        --top;
        return true;
    }
    bool IsEmpty() {
        return top == 0;
    }
    size_t Size() {
        return top;
    }
    void Clear() {
        top = 0;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s) {
    for (size_t i = 0; i < s.top; ++i) {
        os << s.store[i] << " ";
    }
    return os;
}

template <typename T>
class TestCommand {
public:
    enum Command {
        PUSH,
        POP,
        TOP,
        SIZE,
        CLEAR,
        PRINT,
    };
    
    Command command { };
    T value { };
    size_t size { };
};

template <typename T>
bool ExecuteCommand(Stack<T> &s, const TestCommand<T> &cmd) {
    switch (cmd.command) {
        case TestCommand<T>::PUSH:
            s.Push(cmd.value);
            break;
        case TestCommand<T>::POP:
            s.Pop();
            break;
        case TestCommand<T>::TOP:
            if (s.IsEmpty()) return false;
            if (s.Top() != cmd.value) {
                std::cout << "Top value mismatch: expected " << cmd.value << ", got " << s.Top() << std::endl;
                return false;
            }
            break;
        case TestCommand<T>::SIZE:
            if (s.Size() != cmd.size) {
                std::cout << "Size mismatch: expected " << cmd.size << ", got " << s.Size() << std::endl;
                return false;
            }
            break;
        case TestCommand<T>::CLEAR:
            s.Clear();
            break;
        case TestCommand<T>::PRINT:
            std::cout << s << std::endl;
            break;
    }
    return true;
}

template <typename T>
bool TestStack(const std::vector<TestCommand<T>> &commands) {
    Stack<T> stack(1);
    for (const auto &cmd : commands) {
        if (!ExecuteCommand(stack, cmd)) {
            std::cout << "Test failed at command: " << cmd.command << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    const std::vector<std::vector<TestCommand<int>>> testCases = {
        {
            { TestCommand<int>::PUSH, 1 },
            { TestCommand<int>::PUSH, 2 },
            { TestCommand<int>::PUSH, 3 },
            { TestCommand<int>::TOP, 3 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::POP, 0 },
            { TestCommand<int>::TOP, 2 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::CLEAR, 0 },
            { TestCommand<int>::SIZE, 0, 0 },
        }
    };

    for (const auto &testCase : testCases) {
        if (!TestStack(testCase)) {
            std::cout << "Test case failed!" << std::endl;
        } else {
            std::cout << "Test case passed!" << std::endl;
        }
    }

    return 0;
}