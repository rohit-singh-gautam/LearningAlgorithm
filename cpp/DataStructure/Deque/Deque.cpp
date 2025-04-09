#include <iostream>
#include <vector>
#include <memory>

template <typename ValueT>
class Deque {
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const Deque<T> &value);
    size_t capacity;
    std::unique_ptr<ValueT[]> store;
    size_t firstIndex { 0 };
    size_t size { 0 };

    void ResizeIfRequired() {
        if (size < capacity) return;
        auto newStore = new ValueT[capacity * 2];
        for(size_t index = 0; index < size; ++index) {
            newStore[index] = store[(firstIndex + index) % capacity];
        }
        firstIndex = 0;
        capacity *= 2;
        store.reset(newStore);
    }

public:
    Deque(const size_t capacity) : capacity { capacity }, store { new ValueT[capacity] } { }

    template <typename T>
    void PushBack(const T &v) {
        ResizeIfRequired();
        store[(firstIndex + size++) % capacity] = v;
    }

    template <typename T>
    void PushBack(T &&v) {
        ResizeIfRequired();
        store[(firstIndex + size++) % capacity] = std::forward(v);
    }

    template <typename T>
    void PushFront(const T &v) {
        ResizeIfRequired();
        firstIndex = (firstIndex + capacity - 1) % capacity;
        ++size;
        store[firstIndex] = v;
    }

    template <typename T>
    void PushFront(T &&v) {
        ResizeIfRequired();
        firstIndex = (firstIndex + capacity - 1) % capacity;
        ++size;
        store[firstIndex] = std::forward(v);
    }

    bool PopFront() {
        if (size == 0) return false;
        firstIndex = (firstIndex + 1) % capacity;
        --size;
        return true;
    }

    bool PopBack() {
        if (size == 0) return false;
        --size;
        return true;
    }

    ValueT &Front() const {
        return store[firstIndex];
    }

    ValueT &Back() const {
        return store[(firstIndex + size - 1) % capacity];
    }

    void Clear() {
        firstIndex = 0;
        size = 0;
    }

    auto Size() const { return size; }
    auto IsEmpty() const { return size == 0; }
};

template <typename ValueT>
std::ostream &operator<<(std::ostream &os, const Deque<ValueT> &value) {
    for(size_t index { 0 }; index < value.size; ++index) {
        os << value.store[(value.firstIndex + index) % value.capacity] << ' ';
    }
    return os;
}

enum Command {
    PUSH_BACK,
    POP_BACK,
    PUSH_FRONT,
    POP_FRONT,
    CLEAR,
};

template <typename T>
class TestCommand {
public:
    
    Command command;
    size_t size;
    T front;
    T back;
};

template <typename T>
bool ExecuteCommand(Deque<T> &q, const TestCommand<T> &cmd) {
    switch (cmd.command) {
        case PUSH_BACK:
            q.PushBack(cmd.back);
            break;
        case POP_BACK:
            q.PopBack();
            break;
        case PUSH_FRONT:
            q.PushFront(cmd.front);
            break;
        case POP_FRONT:
            q.PopFront();
            break;
        case CLEAR:
            q.Clear();
            break;
    }

    if (q.Size() != cmd.size) {
        std::cout << "Size mismatch: expected " << cmd.size << ", got " << q.Size() << std::endl;
        return false;
    }

    if (cmd.size) {
        if (q.Front() != cmd.front) {
            std::cout << "Deque Front value mismatch: expected " << cmd.front << ", got " << q.Front() << std::endl;
            return false;
        }
        if (q.Back() != cmd.back) {
            std::cout << "Deque Back value mismatch: expected " << cmd.back << ", got " << q.Back() << std::endl;
            return false;
        }
    }
    return true;
}

template <typename T>
bool TestDeque(const std::vector<TestCommand<T>> &commands) {
    Deque<T> q(2);
    size_t commandIndex = 1;
    for (const auto &cmd : commands) {
        if (!ExecuteCommand(q, cmd)) {
            std::cout << "Command failed: " << commandIndex << std::endl;
            return false;
        }
        ++commandIndex;
    }
    return true;
}

int main() {
    const std::vector<std::vector<TestCommand<int>>> testCases = {
        {
            {PUSH_BACK, 1, 10, 10},
            {PUSH_FRONT, 2, 20, 10},
            {PUSH_BACK, 3, 20, 30},
            {PUSH_FRONT, 4, 10, 30},
            {CLEAR, 0, 0, 0},
        },
        {
            { PUSH_BACK, 1, 20, 20 },
            { PUSH_BACK, 2, 20, 5 },
            { POP_FRONT, 1, 5, 5 },
            { PUSH_BACK, 2, 5, 10 },
            { PUSH_BACK, 3, 5, 15 },
            { POP_BACK, 2, 5, 10 },
            { PUSH_BACK, 3, 5, 20 },
            { PUSH_FRONT, 4, 5, 20 },
            { PUSH_FRONT, 5, 10, 20 },
            { PUSH_BACK, 6, 10, 15 },
            { POP_FRONT, 5, 5, 15 },
            { POP_FRONT, 4, 5, 15 },
            { POP_FRONT, 3, 10, 15 },
            { POP_FRONT, 2, 20, 15 },
        },
        {
            { PUSH_BACK, 1, 1, 1 },
            { PUSH_BACK, 2, 1, 2 },
            { PUSH_BACK, 3, 1, 3 },
            { POP_FRONT, 2, 2, 3 },
            { CLEAR, 0, 0, 0 },
            { PUSH_BACK, 1, 1, 1 },
            { PUSH_BACK, 2, 1, 2 },
            { PUSH_BACK, 3, 1, 3 },
            { POP_FRONT, 2, 2, 3 },
        },
        {
            { PUSH_BACK, 1, 1, 1 },
            { PUSH_BACK, 2, 1, 2 },
            { PUSH_BACK, 3, 1, 3 },
            { PUSH_BACK, 4, 1, 5 },
            { POP_FRONT, 3, 2, 5 },
            { CLEAR, 0, 0, 0 },
        },
        {
            { PUSH_BACK, 1, 20, 20 },
            { PUSH_BACK, 2, 20, 5 },
            { POP_FRONT, 1, 5, 5 },
            { POP_FRONT, 0, 0, 0 },
            { PUSH_BACK, 1, 10, 10 },
            { PUSH_BACK, 2, 10, 15 },
            { POP_FRONT, 1, 15, 15 },
            { CLEAR, 0, 0, 0 },
            { PUSH_BACK, 1, 20, 20 },
            { PUSH_BACK, 2, 20, 5 },
            { PUSH_BACK, 3, 20, 10 },
            { PUSH_BACK, 4, 20, 15 },
            { POP_FRONT, 3, 5, 15 },
            { POP_FRONT, 2, 10, 15 },
            { POP_FRONT, 1, 15, 15 },
            { POP_FRONT, 0, 0, 0 },
        },
        {
            { PUSH_BACK, 1, 1, 1 },
            { PUSH_BACK, 2, 1, 2 },
            { PUSH_BACK, 3, 1, 3 },
            { PUSH_BACK, 4, 1, 4 },
            { PUSH_BACK, 5, 1, 5 },
            { POP_FRONT, 4, 2, 5 },
            { CLEAR, 0, 0, 0 },
        },
    };

    size_t testIndex = 1;
    for(const auto &testCase : testCases) {
        std::cout << "Test " << testIndex << " running" << std::endl;
        if (!TestDeque(testCase)) {
            std::cout << "Test case failed!" << std::endl;
        } else {
            std::cout << "Test case passed!" << std::endl;
        }
        ++testIndex;
    }

}
