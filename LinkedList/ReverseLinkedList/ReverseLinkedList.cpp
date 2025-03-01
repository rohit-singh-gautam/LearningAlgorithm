#include <iostream>
#include <vector>
#include <stack>
#include <ranges>

template <typename ValueType>
class LinkedList {
public:
    LinkedList(const ValueType &value, LinkedList<ValueType> *next = nullptr) : value { value }, next { next } { }
    LinkedList(ValueType &&value, LinkedList<ValueType> *next = nullptr) : value { std::move(value) }, next { next } { }

    ValueType value { };
    LinkedList<ValueType> *next { nullptr };
};

template <typename ValueType, bool first = true>
LinkedList<ValueType> *ReverseRecursive(LinkedList<ValueType> *current) {
    if (current == nullptr || current->next == nullptr) return current;
    auto reversed = ReverseRecursive<ValueType, false>(current->next);
    current->next->next = current;
    if constexpr (first) current->next = nullptr;
    return reversed;
}

template <typename ValueType>
LinkedList<ValueType> *ReverseStack(LinkedList<ValueType> *head) {
    if (head == nullptr) return nullptr;
    std::stack<LinkedList<ValueType> *> liststack { };
    while(head) {
        liststack.push(head);
        head = head->next;
    }

    auto newhead = liststack.top();
    liststack.pop();
    auto current = newhead;
    while(!liststack.empty()) {
        current->next = liststack.top();
        current = current->next;
        liststack.pop();
    }
    current->next = nullptr;
    return newhead;
}

template <typename ValueType>
LinkedList<ValueType> *CreateLinkedList(const std::vector<ValueType> &test) {
    auto iterator = std::begin(test);
    const auto end = std::end(test);
    if (iterator == end) return nullptr;
    auto head = new LinkedList<ValueType> { *iterator };
    auto listitr = head;
    iterator = std::next(iterator);
    while (iterator != end)
    {
        listitr->next = new LinkedList<ValueType> { *iterator };
        listitr = listitr->next;
        iterator = std::next(iterator);
    }
    return head;
}

template <typename ValueType>
void DeleteLinkedList(LinkedList<ValueType> *head) {
    while(head) {
        auto next = head->next;
        delete head;
        head = next;
    }
}

template <typename ValueType>
std::ostream &operator<<(std::ostream &os, LinkedList<ValueType> const *head) {
    os << "Linked List: { ";
    while(head) {
        os << head->value << ' ';
        head = head->next;
    }
    return os << '}';
}

template <typename ValueType>
std::ostream &operator<<(std::ostream &os, const std::vector<ValueType> &list) {
    os << "Linked List: { ";
    for(const auto &value: list) {
        os << value << ' ';
    }
    return os << '}';
}

template <typename ValueType>
bool CheckReversed(const std::vector<ValueType> &test, LinkedList<ValueType> const *head) {
    for(const auto &value: std::ranges::reverse_view(test)) {
        if (value != head->value) return false;
        head = head->next;
    }
    return true;
}

template <typename ValueType>
bool TestRecursive(const std::vector<ValueType> &test) {
    auto head = CreateLinkedList(test);
    auto reversed = ReverseRecursive(head);
    std::cout << "Reversed Recursive " << reversed << std::endl;
    if (!CheckReversed(test, reversed)) {
        std::cout << "Failed test\n";
        return false;
    }
    DeleteLinkedList(head);
    return true;
}

template <typename ValueType>
bool TestStack(const std::vector<ValueType> &test) {
    auto head = CreateLinkedList(test);
    auto reversed = ReverseStack(head);
    std::cout << "Reversed Stack " << reversed << std::endl;
    if (!CheckReversed(test, reversed)) {
        std::cout << "Failed test\n";
        return false;
    }
    DeleteLinkedList(head);
    return true;
}

int main(int, char *[]) {
    std::vector<std::vector<int>> testlist {
        {1, 2, 3, 4, 5, 6, 7, 8},
        {8, 7, 6, 5, 4, 3, 2, 1},
        { },
        { 1 },
        { 1, 2 },
        { 1, 2, 3 },
        { 8, 7, 6, 1 },
    };

    for(auto &test: testlist) {
        std::cout << "Original " << test << std::endl;
        if (!TestRecursive(test)) break;
        if (!TestStack(test)) break;
    }

    return 0;
}


