#include <iostream>

template <typename T>
struct Node {
  Node<T>* next = nullptr;
  T value;
  Node(const T& value) : value(value) {}

  ~Node() { /* do not delete next here */ }
};

template <typename T>
class List {
 private:
  Node<T>* _head = nullptr;
  size_t _size = 0;

 public:
  List() {}

  explicit List(size_t size, const T& value) {
    _head = new Node<T>(value);
    Node<T>* current = _head;
    for (size_t i = 1; i < size; ++i) {
      current->next = new Node<T>(value);
      current = current->next;
    }
    _size = size;
  }

  List(const List& other) : _size(other._size) {
    if (other._head) {
      _head = new Node<T>(other._head->value);
      Node<T>* current = _head;
      Node<T>* other_current = other._head->next;
      while (other_current) {
        current->next = new Node<T>(other_current->value);
        current = current->next;
        other_current = other_current->next;
      }
    }
  }

  List(List&& other) noexcept : _head(other._head), _size(other._size) {
    other._head = nullptr;
    other._size = 0;
  }

  List(const std::initializer_list<T>& init) {
    for (const T& value : init) {
      push_back(value);
    }
  }

  void push_back(const T& value) {
    if (!_head) {
      _head = new Node<T>(value);
    } else {
      Node<T>* current = _head;
      while (current->next) {
        current = current->next;
      }
      current->next = new Node<T>(value);
    }
    ++_size;
  }

  void pop_front() {
    if (_size == 0 || _head == nullptr) {
      return;
    }
    Node<T>* temp = _head;
    _head = _head->next;
    delete temp;
    --_size;
  }

  void pop_back() {
    if (_size <= 1) {
      delete _head;
      _head = nullptr;
      _size = 0;
      return;
    }
    Node<T>* current = _head;
    while (current->next->next) {
      current = current->next;
    }
    delete current->next;
    current->next = nullptr;
    --_size;
  }

  void printList() const {
    Node<T>* current = _head;
    while (current) {
      std::cout << current->value << " ";
      current = current->next;
    }
    std::cout << std::endl;
  }

  size_t getSize() const noexcept { return _size; }

  T& get(size_t index) {
    if (index >= _size) {
      throw std::out_of_range("Index out of range");
    }
    Node<T>* current = _head;
    for (size_t i = 0; i < index; i++) {
      current = current->next;
    }
    return current->value;
  }

  T& front() {
    if (!_head) {
      throw std::out_of_range("List is empty");
    }
    return _head->value;
  }

  T& back() {
    if (!_head) {
      throw std::out_of_range("List is empty");
    }
    Node<T>* current = _head;
    while (current->next) {
      current = current->next;
    }
    return current->value;
  }

  bool empty() const noexcept { return _size == 0; }

  void swap(List& other) {
    std::swap(_head, other._head);
    std::swap(_size, other._size);
  }

  ~List() {
    while (_head) {
      Node<T>* temp = _head;
      _head = _head->next;
      delete temp;
    }
  }
};

int main() {
  List<int> list = {1, 2, 3, 4, 5};
  list.printList();
  list.push_back(6);
  std::cout << "List 1 after push_back(6)\n";
  list.printList();
  list.pop_front();
  list.printList();
  std::cout << "List 1 pop_front\n";
  list.pop_back();
  list.printList();
  std::cout << "List 1 pop_back\n";

  List<int> list2 = list;
  std::cout << "List 2 copy list1\n";
  list2.printList();
  list2.pop_back();
  list2.printList();

  List<int> list3 = std::move(list2);
  std::cout << "List 3 \n";
  list3.printList();
  list3.pop_back();
  list3.pop_back();
  list3.printList();

  return 0;
}
