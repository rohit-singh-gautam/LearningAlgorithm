#include <iostream>
#include <vector>
#include <memory>

template <typename ValueT>
class Queue {
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
class TestCommand {
public:
    enum Command {
        ENQUEUE,
        DEQUEUE,
        FRONT,
        SIZE,
        CLEAR,
        PRINT,
    };
    
    Command command { };
    T value { };
    size_t size { };
};

template <typename T>
bool ExecuteCommand(Queue<T> &q, const TestCommand<T> &cmd) {
    switch (cmd.command) {
        case TestCommand<T>::ENQUEUE:
            q.Enqueue(cmd.value);
            break;
        case TestCommand<T>::DEQUEUE:
            if (q.IsEmpty()) {
                std::cout << "Queue is empty, cannot get front value." << std::endl;
                return false;
            }
            q.Dequeue();
            break;
        case TestCommand<T>::FRONT:
            if (q.IsEmpty()) {
                std::cout << "Queue is empty, cannot get front value." << std::endl;
                return false;
            }
            if (q.Front() != cmd.value) {
                std::cout << "Front value mismatch: expected " << cmd.value << ", got " << q.Front() << std::endl;
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
            std::cout << "Queue: " << q << std::endl;
            break;
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
            { TestCommand<int>::ENQUEUE, 1 },
            { TestCommand<int>::ENQUEUE, 2 },
            { TestCommand<int>::ENQUEUE, 3 },
            { TestCommand<int>::FRONT, 1 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 2 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
        },
        {
            { TestCommand<int>::ENQUEUE, 1 },
            { TestCommand<int>::ENQUEUE, 2 },
            { TestCommand<int>::ENQUEUE, 3 },
            { TestCommand<int>::ENQUEUE, 5 },
            { TestCommand<int>::FRONT, 1 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 2 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
        },
        {
            { TestCommand<int>::ENQUEUE, 20 },
            { TestCommand<int>::ENQUEUE, 5 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::ENQUEUE, 10 },
            { TestCommand<int>::ENQUEUE, 15 },
            { TestCommand<int>::FRONT, 10 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 15 },
            { TestCommand<int>::SIZE, 0, 1 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
            { TestCommand<int>::ENQUEUE, 20 },
            { TestCommand<int>::ENQUEUE, 5 },
            { TestCommand<int>::ENQUEUE, 10 },
            { TestCommand<int>::ENQUEUE, 15 },
            { TestCommand<int>::FRONT, 20 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 5 },
            { TestCommand<int>::SIZE, 0, 3 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 10 },
            { TestCommand<int>::SIZE, 0, 2 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 15 },
            { TestCommand<int>::SIZE, 0, 1 },
            { TestCommand<int>::DEQUEUE },
        },
        {
            { TestCommand<int>::ENQUEUE, 1 },
            { TestCommand<int>::ENQUEUE, 2 },
            { TestCommand<int>::ENQUEUE, 3 },
            { TestCommand<int>::ENQUEUE, 4 },
            { TestCommand<int>::ENQUEUE, 5 },
            { TestCommand<int>::FRONT, 1 },
            { TestCommand<int>::SIZE, 0, 5 },
            { TestCommand<int>::DEQUEUE },
            { TestCommand<int>::FRONT, 2 },
            { TestCommand<int>::SIZE, 0, 4 },
            { TestCommand<int>::CLEAR },
            { TestCommand<int>::SIZE, 0 },
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