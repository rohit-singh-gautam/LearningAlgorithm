#include <iostream>
#include <vector>

template <typename ValueT>
class Queue {
    template <typename T>
    friend std::ostream &operator<<(std::ostream &os, const Queue<T> &q);
    ValueT *store { };
    size_t size;

    size_t front { 0 };
    size_t back { 0 };

    void Resize() {
        size_t newsize = size * 2;
        ValueT *newStore = new ValueT[newsize];
        size_t count { 0 };
        while((front + count) != back) {
            newStore[count] = std::move(store[(front + count) % size]);
            ++count;
        }
        front = 0;
        back = count;
        size = newsize;
        delete[] store;
        store = newStore;
    }

public:
    Queue(size_t size) : store { new ValueT[size]}, size { size }, front { 0 }, back { 0 } { }
    Queue(const Queue &) = delete;

    ~Queue() {
        delete[] store;
    }

    Queue & operator=(const Queue &) = delete;

    template <typename T>
    void Enqueue(const T &v) {
        auto newback = (back + 1) % size;
        if (front == newback) {
            Resize();
            newback = (back + 1) % size;
        }
        store[back] = v;
        back = newback;
    }

    template <typename T>
    void Enqueue(T &&v) {
        auto newback = (back + 1) % size;
        if (front == newback) {
            Resize();
            newback = (back + 1) % size;
        }
        store[back] = std::forward(v);
        back = newback;
    }

    ValueT &Front() {
        return store[front];
    }

    bool Dequeue() {
        if (front == back) {
            return false;
        }
        front = (front + 1) % size;
        return true;
    }

    bool IsEmpty() {
        return front == back;
    }

    size_t Size() {
        return (back - front + size) % size;
    }
    void Clear() {
        front = 0;
        back = 0;
    }
    void Print() const {
        for (size_t i = front; i != back; i = (i + 1) % size) {
            std::cout << store[i] << " ";
        }
        std::cout << std::endl;
    }
};


template <typename T>
std::ostream &operator<<(std::ostream &os, const Queue<T> &q) {
    for (size_t i = q.front; i != q.back; i = (i + 1) % q.size) {
        os << q.store[i] << " ";
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
            q.Dequeue();
            break;
        case TestCommand<T>::FRONT:
            if (q.IsEmpty()) return false;
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
            q.Print();
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
    std::cout << "Final Queue: " << q << std::endl;
    std::cout << "Final Size: " << q.Size() << std::endl;
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
        }
    };

    for(const auto &testCase : testCases) {
        std::cout << "Running test case..." << std::endl;
        if (!TestQueue(testCase)) {
            std::cout << "Test case failed!" << std::endl;
        } else {
            std::cout << "Test case passed!" << std::endl;
        }
    }

}