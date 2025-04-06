#include <iostream>
#include <vector>
#include <memory>

template <typename ValueT>
class Stack {
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const Stack<T> &s);
    std::unique_ptr<ValueT[]> store;
    size_t capacity;
    size_t size { 0 };

    void ResizeIfRequired() {
        if (size + 1 < capacity) {
            return;
        }
        size_t newcapacity = capacity * 2;
        auto newStore = new ValueT[newcapacity];
        for (size_t i = 0; i < capacity; ++i) {
            newStore[i] = std::move(store[i]);
        }
        store.reset(newStore);
        capacity = newcapacity;
    }
public:
    Stack(size_t capacity) : store { new ValueT[capacity] }, capacity { capacity } { }
    Stack(const Stack &) = delete;
    Stack & operator=(const Stack &) = delete;

    template <typename T>
    void Push(const T &v) {
        ResizeIfRequired();
        store[size++] = v;
    }

    template <typename T>
    void Push(T &&v) {
        ResizeIfRequired();
        store[size++] = std::forward(v);
    }
    ValueT &Top() {
        return store[size - 1];
    }
    bool Pop() {
        if (size == 0) {
            return false;
        }
        --size;
        return true;
    }
    bool IsEmpty() {
        return size == 0;
    }
    size_t Size() {
        return size;
    }
    void Clear() {
        size = 0;
    }
};

template <typename T>
std::ostream &operator<<(std::ostream &os, const Stack<T> &s) {
    for (size_t i = 0; i < s.size; ++i) {
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
        },
        {
            { TestCommand<int>::PUSH, 3 },
            { TestCommand<int>::PUSH, 1 },
            { TestCommand<int>::PUSH, 2 },
            { TestCommand<int>::PUSH, 3 },
            { TestCommand<int>::PUSH, 8 },
            { TestCommand<int>::TOP, 8 },
            { TestCommand<int>::SIZE, 0, 5 },
            { TestCommand<int>::POP, 0 },
            { TestCommand<int>::TOP, 3 },
            { TestCommand<int>::SIZE, 0, 4 },
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