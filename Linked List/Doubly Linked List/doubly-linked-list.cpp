#include <iostream>
#include <unordered_map>
#include <cassert>
#include <stdexcept>

using namespace std;

template <typename T>
struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
    T value = 0;

    Node() {}
    Node(const T &value) : value(value) {}

    friend void swap(Node<T>& lhs, Node<T>& rhs) {
        using std::swap;
        swap(lhs.next, rhs.next);
        swap(lhs.prev, rhs.prev);
        swap(lhs.value, rhs.value);
    }
};

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    size_t _size = 0;

public:
    DoublyLinkedList() {};
    explicit DoublyLinkedList(size_t sz, const T &value);
    DoublyLinkedList(const DoublyLinkedList &other);
    DoublyLinkedList(DoublyLinkedList &&other) noexcept;
    DoublyLinkedList(const std::initializer_list<T> &init);

    ~DoublyLinkedList();

    void push_back(const T &value);
    void push_front(const T &value);

    void pop_back();
    void pop_front();

    // This operation reverses the nodes in the doubly linked list so that the first node becomes the last node while the last node becomes the first node.
    void reverse();

    T &front();
    T &back();

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear(); //

    template <typename U>
    friend void swap(DoublyLinkedList<U>& lhs, DoublyLinkedList<U>& rhs);
    // removes duplicates
    void unique();

    void sort();

    void printList();

    friend auto operator<=>(const DoublyLinkedList &lhs, const DoublyLinkedList &rhs) noexcept
    {
        return lhs._size <=> rhs._size;
    }
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(size_t sz, const T &value)
{
    head = new Node<T>(value);

    Node<T> *current = head;

    for (size_t i = 1; i < sz; ++i)
    {
        current->next = new Node<T>(value);
        current->next->prev = current;
        current = current->next;
    }
    tail = current;
    _size = sz;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList()
{
    while (head)
    {
        Node<T> *current = head;
        head = head->next;
        delete current;
    }
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &other) : _size(other._size)
{
    head = new Node(other.head->value);

    Node<T> *current = head;
    Node<T> *otherCurrent = other.head;
    while (otherCurrent)
    {
        current->next = new Node<T>(otherCurrent->value);
        current->next->prev = current;
        current = current->next;
        otherCurrent = otherCurrent->next;
    }
    tail = current;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList &&other) noexcept : head(other.head), tail(other.tail), _size(other._size)
{
    other.head = nullptr;
    other.tail = nullptr;
    other._size = 0;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const std::initializer_list<T> &init)
{
    for (const T &value : init)
    {
        push_back(value);
    }
}

template <typename T>
size_t DoublyLinkedList<T>::size() const noexcept
{
    return _size;
}

template <typename T>
bool DoublyLinkedList<T>::empty() const noexcept
{
    return _size == 0;
}

template <typename T>
void DoublyLinkedList<T>::push_back(const T &value)
{
    if (!head)
    {
        head = new Node<T>(value);
        tail = head;
    }
    else
    {
        tail->next = new Node<T>(value);
        tail->next->prev = tail;
        tail = tail->next;
    }
    ++_size;
}

template <typename T>
void DoublyLinkedList<T>::push_front(const T &value)
{
    if (!head)
    {
        head = new Node<T>(value);
        tail = head;
    }
    else
    {
        head->prev = new Node<T>(value);
        head->prev->next = head;
        head = head->prev;
    }
    ++_size;
}

template <typename T>
void DoublyLinkedList<T>::pop_back()
{
    if (_size == 0)
    {
        return;
    }
    if (_size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        _size = 0;
        return;
    }
    Node<T> *current = tail;
    tail = tail->prev;
    delete current;
    tail->next = nullptr;
    --_size;
}

template <typename T>
void DoublyLinkedList<T>::pop_front()
{
    if (_size == 0)
    {
        return;
    }
    if (_size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        _size = 0;
        return;
    }
    Node<T> *current = head;
    head = head->next;
    delete current;
    head->prev = nullptr;
    --_size;
}

template <typename T>
T& DoublyLinkedList<T>::front()
{
    if (_size == 0)
        throw std::out_of_range("List is empty");
    return head->value;
}

template <typename T>
T& DoublyLinkedList<T>::back()
{
    if (_size == 0)
        throw std::out_of_range("List is empty");
    return tail->value;
}

template <typename T>
void DoublyLinkedList<T>::unique()
{
    std::unordered_map<T, bool> uniqueMap;

    Node<T> *current = head;
    while (current)
    {
        if (uniqueMap[current->value])
        {
            Node<T> *temp = current;
            if (current->prev) current->prev->next = current->next;
            if (current->next) current->next->prev = current->prev;
            if (current == tail)
            {
                tail = current->prev;
            }
            current = current->next;
            delete temp;
            --_size;
        }
        else
        {
            uniqueMap[current->value] = true;
            current = current->next;
        }
    }
}

template <typename T>
void DoublyLinkedList<T>::reverse()
{
    Node<T> *current = head;
    Node<T> *temp = nullptr;

    while (current)
    {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev;
    }

    if (temp)
    {
        head = temp->prev;
    }
}

template <typename T>
void swap(DoublyLinkedList<T>& lhs, DoublyLinkedList<T>& rhs) {
    using std::swap;
    swap(lhs.head, rhs.head);
    swap(lhs.tail, rhs.tail);
    swap(lhs._size, rhs._size);
}
/*
template <typename T>
void DoublyLinkedList<T>::sort() {
    if (_size <= 1) {
        return;
    }
    Node<T>* current = head;
    Node<T>* temp = nullptr;

    while (current) {
        temp = current->next;
        while (temp) {
            if (current->value > temp->value) {
                // Використовуємо функцію swap для обміну вузлів
                swap(*current, *temp);
            }
            temp = temp->next;
        }
        current = current->next;
    }
}
*/

template <typename T>
void DoublyLinkedList<T>::printList()
{
    Node<T>* current = head;

    while(current) {
        std::cout << current->value << ' ';
        current = current->next;
    }

    std::cout << '\n';
}

void runTests() {
    // Test case 1: Create an empty list
    DoublyLinkedList<int> emptyList;
    assert(emptyList.empty());

    // Test case 2: Create a list with initial values
    DoublyLinkedList<int> list1 = {1, 2, 3};
    assert(list1.size() == 3);
    assert(list1.front() == 1);
    assert(list1.back() == 3);

    // Test case 3: Push elements to the back of the list
    list1.push_back(4);
    assert(list1.size() == 4);
    assert(list1.back() == 4);

    // Test case 4: Push elements to the front of the list
    list1.push_front(0);
    assert(list1.size() == 5);
    assert(list1.front() == 0);

    // Test case 5: Pop elements from the front of the list
    list1.pop_front();
    assert(list1.size() == 4);
    assert(list1.front() == 1);

    // Test case 6: Pop elements from the back of the list
    list1.pop_back();
    assert(list1.size() == 3);
    assert(list1.back() == 3);

    // Test case 7: Remove duplicate elements from the list
    list1.push_back(2);
    list1.push_back(3);
    list1.unique();
    assert(list1.size() == 3);
    assert(list1.front() == 1);
    assert(list1.back() == 3);

    DoublyLinkedList<int> list = {1, 15, 3, 4, 4, 2, 7, 8, 23, 10};

    list.push_back(11);
    list.push_front(0);
    list.printList();

    list.pop_front();
    list.pop_back();
    list.printList();

    list.unique();
    list.printList();

    list.reverse();
    list.printList();

    list.sort();
    list.printList();

    std::cout << "All tests passed!" << std::endl;
}

int main() {
    runTests();

    return 0;
}
