#include <atomic>
#include <vector>
#include <memory>
#include <functional>
#include <iostream>

template <typename Key, typename Value>
class SplitOrderMap {
protected:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key { k }, value { v }, next { nullptr } {}
        Node(const Key& k, Value&& v) : key { k }, value { std::move(v) }, next { nullptr } {}
        Node(Key&& k, const Value& v) : key { std::move(k) }, value { v }, next { nullptr } {}
        Node(Key&& k, Value&& v) : key { std::move(k) }, value { std::move(v) }, next { nullptr } {}
        Node(const Node &) = delete;
        Node& operator=(const Node &) = delete;
    };

    struct Bucket {
        std::mutex lock { };
        Node* head { nullptr };

        Bucket() = default;
        Bucket(const Bucket &rhs) : head { rhs.head } { }
        Bucket& operator=(const Bucket &rhs) { head = rhs.head; return *this; }
    };

    std::vector<Bucket> table;
    std::atomic<size_t> size;
    size_t capacity;

public:
    SplitOrderMap(size_t initial_capacity = 16)
        : table { }, size { 0 }, capacity { initial_capacity } {
            table.resize(capacity, { });
    }

    SplitOrderMap(const SplitOrderMap& rhs) = default;
    SplitOrderMap(SplitOrderMap&& rhs) : table { std::move(rhs.table) }, size { rhs.size.load() }, capacity { rhs.capacity }  { }
    SplitOrderMap& operator=(const SplitOrderMap& rhs) = default;

    constexpr size_t get_index(const Key& key) const {
        size_t hash = std::hash<Key>{}(key);
        return hash % capacity;
    }

    bool insert(size_t index, Node *new_node) {
        auto &bucket = table[index];
        std::lock_guard<std::mutex> lock(bucket.lock);
        while (true) {
            if (bucket.head == nullptr) {
                bucket.head = new_node;
                size.fetch_add(1, std::memory_order_relaxed);
                return true;
            } else {
                Node* current = bucket.head;
                while (current) {
                    if (current->key == new_node->key) {
                        delete new_node;
                        return false;
                    }
                    current = current->next;
                }
                new_node->next = bucket.head;
                bucket.head = new_node;
                size.fetch_add(1, std::memory_order_relaxed);
                return true;
            }
        }
    }

    bool insert(const Key& key, const Value& value) {
        size_t index = get_index(key);
        auto new_node = new Node(key, value);
        return insert(index, new_node);
    }


    bool insert(const Key& key, Value&& value) {
        size_t index = get_index(key);
        auto new_node = new Node(key, std::move(value));
        return insert(index, new_node);
    }

    bool insert(Key&& key, Value&& value) {
        size_t index = get_index(key);
        auto new_node = new Node(std::move(key), std::move(value));
        return insert(index, new_node);
    }

    bool remove(const Key& key) {
        size_t index = get_index(key);
        auto &bucket = table[index];
        std::lock_guard<std::mutex> lock(bucket.lock);

        Node* current = bucket.head;
        Node* prev = nullptr;

        while (current) {
            if (current->key == key) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    bucket.head = current->next;
                }
                delete current;
                size.fetch_sub(1, std::memory_order_relaxed);
                return true;
            }
            prev = current;
            current = current->next;
        }
        return false;
    }

    bool find(const Key& key, Value &value) {
        auto valueopt = find(key);
        if (valueopt) {
            value = valueopt.value();
            return true;
        } else {
            return false;
        }
    }

    std::optional<std::reference_wrapper<Value>> find(const Key& key) {
        size_t index = get_index(key);
        auto &bucket = table[index];
        std::lock_guard<std::mutex> lock(bucket.lock);

        Node* current = bucket.head;
        while (current) {
            if (current->key == key) {
                return current->value;
            }
            current = current->next;
        }
        return std::nullopt;
    }

    bool contains(const Key& key) {
        size_t index = get_index(key);
        auto &bucket = table[index];
        std::lock_guard<std::mutex> lock(bucket.lock);

        Node* current = bucket.head;
        while (current) {
            if (current->key == key) {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    size_t get_size() const {
        return size.load(std::memory_order_relaxed);
    }

}; // class SplitOrderMap

int main() {
    SplitOrderMap<int, std::string> som(4);

    som.insert(10, "ten");
    som.insert(20, "twenty");
    som.insert(30, "thirty");

    std::string value;
    std::cout << "Find 20: " << (som.find(20, value) ? value : "not found") << "\n";
    std::cout << "Erase 20: " << som.remove(20) << "\n";
    std::cout << "Find 20: " << (som.find(20, value) ? value : "not found") << "\n";

    return 0;
}
