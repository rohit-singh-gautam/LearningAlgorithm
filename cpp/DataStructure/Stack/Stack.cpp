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
        if (size < capacity) return;
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

enum Command {
    PUSH,
    POP,
    CLEAR,
};

template <typename T>
class TestCommand {
public:
    
    Command command;
    size_t size;
    T value;
};

template <typename T>
bool ExecuteCommand(Stack<T> &s, const TestCommand<T> &cmd) {
    switch (cmd.command) {
        case PUSH:
            s.Push(cmd.value);
            break;
        case POP:
            s.Pop();
            break;
        case CLEAR:
            s.Clear();
            break;
    }
    if (cmd.size != s.Size()) {
        std::cout << "Test failed at size expected: " << cmd.size << ", got: " << s.Size() << std::endl;
        return false;
    }
    if (cmd.size) {
        if (cmd.value != s.Top()) {
            std::cout << "Test failed top expected: " << cmd.value << ", got: " << s.Top() << std::endl;
        }
    }
    return true;
}

template <typename T>
bool TestStack(const std::vector<TestCommand<T>> &commands) {
    Stack<T> stack(1);
    size_t commandIndex = 0;
    for (const auto &cmd : commands) {
        if (!ExecuteCommand(stack, cmd)) {
            std::cout << "Test failed at command(" << commandIndex << "): " << cmd.command << std::endl;
            return false;
        }
        ++commandIndex;
    }
    return true;
}

int main() {
    const std::vector<std::vector<TestCommand<int>>> testCases = {
        {
            { PUSH, 1, 1 },
            { PUSH, 2, 2 },
            { PUSH, 3, 3 },
            { POP, 2, 2 },
            { CLEAR, 0, 0 },
        },
        {
            { PUSH, 1, 3 },
            { PUSH, 2, 1 },
            { PUSH, 3, 2 },
            { PUSH, 4, 3 },
            { PUSH, 5, 8 },
            { POP, 4, 3 },
            { CLEAR, 0, 0 },
        },
        {
			{PUSH, 1, 10},
			{PUSH, 2, 20},
			{POP, 1, 10},
			{PUSH, 2, 30},
		},
		{
			{PUSH, 1, 10},
			{PUSH, 2, 20},
			{PUSH, 3, 40},
			{PUSH, 4, 80},
			{PUSH, 5, 20},
			{PUSH, 6, 100},
			{POP, 5, 20},
			{PUSH, 6, 30},
			{CLEAR, 0, 0},
		},
    };

    size_t testIndex = 1;
    for (const auto &testCase : testCases) {
        std::cout << "Testing: " << testIndex << std::endl;
        if (!TestStack(testCase)) {
            std::cout << "Test case failed!" << std::endl;
        } else {
            std::cout << "Test case passed!" << std::endl;
        }
        ++testIndex;
    }

    return 0;
}