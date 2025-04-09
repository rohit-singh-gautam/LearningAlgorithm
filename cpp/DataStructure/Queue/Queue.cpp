#include <iostream>
#include <vector>
#include <memory>

enum Command {
    ENQUEUE,
    DEQUEUE,
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

template <typename ValueT>
class Queue {
    template <typename T>
    friend bool ExecuteCommand(Queue<T> &q, const TestCommand<T> &cmd);
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &q);
    std::unique_ptr<ValueT[]> store { };
    size_t capacity { 0 };

    size_t frontIndex { 0 };
    size_t size { 0 };

    void ResizeIfRequired() {
        if (size < capacity) return;
        size_t newcapacity = capacity * 2;
        ValueT *newStore = new ValueT[newcapacity];
        size_t count { 0 };
        while(count < size) {
            newStore[count] = std::move(store[(frontIndex + count) % capacity]);
            ++count;
        }
        frontIndex = 0;
        capacity = newcapacity;
        store.reset(newStore);
    }

    ValueT &Back() const {
        return store[(frontIndex + size - 1) % capacity];
    }

public:
    Queue(size_t capacity) : store { new ValueT[capacity] }, capacity { capacity } { }
    Queue(const Queue &) = delete;

    Queue & operator=(const Queue &) = delete;

    template <typename T>
    void Enqueue(const T &v) {
        ResizeIfRequired();
        store[(frontIndex + size++) % capacity] = v;
    }

    template <typename T>
    void Enqueue(T &&v) {
        ResizeIfRequired();
        store[(frontIndex + size++) % capacity] = std::forward(v);
    }

    ValueT &Front() {
        return store[frontIndex];
    }

    bool Dequeue() {
        if (!size) {
            return false;
        }
        frontIndex = (frontIndex + 1) % capacity;
        --size;
        return true;
    }

    bool IsEmpty() {
        return !size;
    }

    size_t Size() {
        return size;
    }

    size_t Capacity() {
        return capacity;
    }

    void Clear() {
        frontIndex = 0;
        size = 0;
    }
};


template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q) {
    for (size_t i = 0; i < q.size; ++i) {
        os << q.store[(q.frontIndex + i) % q.capacity] << " ";
    }
    return os;
}

template <typename T>
bool ExecuteCommand(Queue<T> &q, const TestCommand<T> &cmd) {
    switch (cmd.command) {
        case ENQUEUE:
            q.Enqueue(cmd.back);
            break;
        case DEQUEUE:
            if (q.IsEmpty()) {
                std::cout << "Queue is empty, cannot get front value." << std::endl;
                return false;
            }
            q.Dequeue();
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
            std::cout << "Queue Front value mismatch: expected " << cmd.front << ", got " << q.Front() << std::endl;
            return false;
        }
        if (q.Back() != cmd.back) {
            std::cout << "Queue Back value mismatch: expected " << cmd.back << ", got " << q.Back() << std::endl;
            return false;
        }
    }
    return true;
}

template <typename T>
bool TestQueue(const std::vector<TestCommand<T>> &commands) {
    Queue<T> q(2);
    for (const auto &cmd : commands) {
        if (!ExecuteCommand(q, cmd)) {
            std::cout << "Command failed: " << cmd.command << std::endl;
            return false;
        }
    }
    return true;
}


int main(int, char *[]) {
    const std::vector<std::vector<TestCommand<int>>> testCases = {
        {
            { ENQUEUE, 1, 1, 1 },
            { ENQUEUE, 2, 1, 2 },
            { ENQUEUE, 3, 1, 3 },
            { DEQUEUE, 2, 2, 3 },
            { CLEAR, 0, 0, 0 },
        },
        {
            { ENQUEUE, 1, 1, 1 },
            { ENQUEUE, 2, 1, 2 },
            { ENQUEUE, 3, 1, 3 },
            { ENQUEUE, 4, 1, 5 },
            { DEQUEUE, 3, 2, 5 },
            { CLEAR, 0, 0, 0 },
        },
        {
            { ENQUEUE, 1, 20, 20 },
            { ENQUEUE, 2, 20, 5 },
            { DEQUEUE, 1, 5, 5 },
            { DEQUEUE, 0, 0, 0 },
            { ENQUEUE, 1, 10, 10 },
            { ENQUEUE, 2, 10, 15 },
            { DEQUEUE, 1, 15, 15 },
            { CLEAR, 0, 0, 0 },
            { ENQUEUE, 1, 20, 20 },
            { ENQUEUE, 2, 20, 5 },
            { ENQUEUE, 3, 20, 10 },
            { ENQUEUE, 4, 20, 15 },
            { DEQUEUE, 3, 5, 15 },
            { DEQUEUE, 2, 10, 15 },
            { DEQUEUE, 1, 15, 15 },
            { DEQUEUE, 0, 0, 0 },
        },
        {
            { ENQUEUE, 1, 1, 1 },
            { ENQUEUE, 2, 1, 2 },
            { ENQUEUE, 3, 1, 3 },
            { ENQUEUE, 4, 1, 4 },
            { ENQUEUE, 5, 1, 5 },
            { DEQUEUE, 4, 2, 5 },
            { CLEAR, 0, 0, 0 },
        }   
    };

    for(const auto &testCase : testCases) {
        if (!TestQueue(testCase)) {
            std::cout << "Test case failed!" << std::endl;
        } else {
            std::cout << "Test case passed!" << std::endl;
        }
    }

}