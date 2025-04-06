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

template <typename T>
class TestCommand {
public:
    enum Command {
        PUSH_BACK,
        POP_BACK,
        PUSH_FRONT,
        POP_FRONT,
        FRONT,
        BACK,
        SIZE,
        CLEAR,
        PRINT,
    };
    
    Command command { };
    T value { };
    size_t size { };
};

template <typename T>
bool ExecuteCommand(Deque<T> &q, const TestCommand<T> &cmd) {
    switch (cmd.command) {
        case TestCommand<T>::PUSH_BACK:
            q.PushBack(cmd.value);
            break;
        case TestCommand<T>::POP_BACK:
            q.PopBack();
            break;
        case TestCommand<T>::PUSH_FRONT:
            q.PushFront(cmd.value);
            break;
        case TestCommand<T>::POP_FRONT:
            q.PopFront();
            break;
        case TestCommand<T>::FRONT:
            if (q.IsEmpty()) {
                std::cout << "Deque is empty, cannot get front value." << std::endl;
                return false;
            }
            if (q.Front() != cmd.value) {
                std::cout << "Deque Front value mismatch: expected " << cmd.value << ", got " << q.Front() << std::endl;
                return false;
            }
            break;
        case TestCommand<T>::BACK:
            if (q.IsEmpty()) {
                std::cout << "Deque is empty, cannot get back value." << std::endl;
                return false;
            }
            if (q.Back() != cmd.value) {
                std::cout << "Deque Back value mismatch: expected " << cmd.value << ", got " << q.Back() << std::endl;
                return false;
            }
            break;
        case TestCommand<T>::SIZE:
            if (q.Size() != cmd.size) {
                std::cout << "Size mismatch: expected " << cmd.size << ", got " << q.Size() << std::endl;
                return false;
            }
            break;
        case TestCommand<T>::CLEAR:
            q.Clear();
            break;
        case TestCommand<T>::PRINT:
            std::cout << "Deque: " << q << std::endl;
            break;
    }
    return true;
}

template <typename T>
bool TestDeque(const std::vector<TestCommand<T>> &commands) {
    Deque<T> q(2);
    for (const auto &cmd : commands) {
        if (!ExecuteCommand(q, cmd)) {
            std::cout << "Command failed: " << cmd.command << std::endl;
            return false;
        }
    }
    return true;
}

int main() {
    const std::vector<std::vector<TestCommand<int>>> testCases = {
        {
            { TestCommand<int>::PUSH_BACK, 20 },
            { TestCommand<int>::PUSH_BACK, 5 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::PUSH_BACK, 10 },
            { TestCommand<int>::PUSH_BACK, 15 },
            { TestCommand<int>::FRONT, 5 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::POP_BACK },
            { TestCommand<int>::BACK, 10 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::PUSH_BACK, 20 },
            { TestCommand<int>::PUSH_FRONT, 5 },
            { TestCommand<int>::PUSH_FRONT, 10 },
            { TestCommand<int>::PUSH_BACK, 15 },
            { TestCommand<int>::FRONT, 10 },
            { TestCommand<int>::SIZE, 0, 6 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 5 },
            { TestCommand<int>::SIZE, 0, 5 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 5 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 10 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::SIZE, 0, 2 },
        },
        {
            { TestCommand<int>::PUSH_BACK, 1 },
            { TestCommand<int>::PUSH_BACK, 2 },
            { TestCommand<int>::PUSH_BACK, 3 },
            { TestCommand<int>::FRONT, 1 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 2 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
        },
        {
            { TestCommand<int>::PUSH_BACK, 1 },
            { TestCommand<int>::PUSH_BACK, 2 },
            { TestCommand<int>::PUSH_BACK, 3 },
            { TestCommand<int>::PUSH_BACK, 5 },
            { TestCommand<int>::FRONT, 1 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 2 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
        },
        {
            { TestCommand<int>::PUSH_BACK, 20 },
            { TestCommand<int>::PUSH_BACK, 5 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::PUSH_BACK, 10 },
            { TestCommand<int>::PUSH_BACK, 15 },
            { TestCommand<int>::FRONT, 10 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 15 },
            { TestCommand<int>::SIZE, 0, 1 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
            { TestCommand<int>::PUSH_BACK, 20 },
            { TestCommand<int>::PUSH_BACK, 5 },
            { TestCommand<int>::PUSH_BACK, 10 },
            { TestCommand<int>::PUSH_BACK, 15 },
            { TestCommand<int>::FRONT, 20 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 5 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 10 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 15 },
            { TestCommand<int>::SIZE, 0, 1 },
            { TestCommand<int>::POP_FRONT },
        },
        {
            { TestCommand<int>::PUSH_BACK, 1 },
            { TestCommand<int>::PUSH_BACK, 2 },
            { TestCommand<int>::PUSH_BACK, 3 },
            { TestCommand<int>::PUSH_BACK, 4 },
            { TestCommand<int>::PUSH_BACK, 5 },
            { TestCommand<int>::FRONT, 1 },
            { TestCommand<int>::SIZE, 0, 5 },
            { TestCommand<int>::POP_FRONT },
            { TestCommand<int>::FRONT, 2 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
        },
    };

    for(const auto &testCase : testCases) {
        if (!TestDeque(testCase)) {
            std::cout << "Test case failed!" << std::endl;
        } else {
            std::cout << "Test case passed!" << std::endl;
        }
    }

}
