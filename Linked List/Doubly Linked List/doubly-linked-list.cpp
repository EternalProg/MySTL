#include <iostream>

template <typename T>
struct Node
{
    Node *next = nullptr;
    Node *prev = nullptr;
    T value = 0;

    Node() {}
    Node(const T &value) : value(value) {}
};

template <typename T>
class DoublyLinkedList
{
private:
    Node<T> *head = nullptr;
    Node<T> *tail = nullptr;
    size_t size = 0;

public:
    DoublyLinkedList();
    explicit DoublyLinkedList(size_t sz, const T &value);
    DoublyLinkedList(const DoublyLinkedList &other);
    DoublyLinkedList(DoublyLinkedList &&other) noexcept;
    DoublyLinkedList(const std::initializer_list<T> &init);

    ~DoublyLinkedList(){};

    void push_back(const T &value);
    void push_front(const T &value);

    void pop_back();
    void pop_front();

    // This operation reverses the nodes in the doubly linked list so that the first node becomes the last node while the last node becomes the first node.
    void reverse(); //

    // return first/last element
    T &front();
    T &back();

    bool empty() const noexcept;
    size_t size() const noexcept;

    void clear(); //

    void swap(); //

    // removes duplicates
    void unique(); //

    void sort(); //

    friend auto operator<=>(const DoublyLinkedList &lhs, const DoublyLinkedList &rhs) noexcept
    {
        return lhs.size <=> rhs.size;
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
    size = sz;
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
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList &other) : size(other.size)
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
DoublyLinkedList<T>::DoublyLinkedList(DoublyLinkedList &&other) noexcept : head(other.head), tail(other.tail), size(other.size)
{
    other.head = nullptr;
    other.tail = nullptr;
    other.size = 0;
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
    return size;
}

template <typename T>
bool DoublyLinkedList<T>::empty() const noexcept
{
    return size == 0;
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
    ++size;
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
    ++size;
}

template <typename T>
void DoublyLinkedList<T>::pop_back()
{
    if (size == 0)
    {
        return;
    }
    if (size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }
    Node<T> *current = tail;
    tail = tail->prev;
    delete current;
    tail->next = nullptr;
    --size;
}

template <typename T>
void DoublyLinkedList<T>::pop_front()
{
    if (size == 0)
    {
        return;
    }
    if (size == 1)
    {
        delete head;
        head = nullptr;
        tail = nullptr;
        size = 0;
        return;
    }
    Node<T> *current = head;
    head = head->next;
    delete current;
    head->prev = nullptr;
    --size;
}

template <typename T>
T &DoublyLinkedList<T>::front()
{
    if (size == 0)
        throw std::out_of_range("List is empty");
    return head->value;
}

template <typename T>
T &DoublyLinkedList<T>::front()
{
    if (size == 0)
        throw std::out_of_range("List is empty");
    return head->value;
}
