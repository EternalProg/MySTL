#include <cstdlib>
#include <iostream>
#include <memory>

template <typename T>
class Queue {
 private:
  T *arr = nullptr;
  size_t m_size = 0;
  size_t m_capacity = 0;
  int frontIndex = 0;

  void reserve(const size_t _capacity) {
    if (_capacity <= m_capacity) return;

    T *newarr = new T[_capacity];
    for (size_t i = 0; i < m_size; ++i) {
      newarr[i] = arr[(frontIndex + i) % m_capacity];
    }
    delete[] arr;
    arr = newarr;
    m_capacity = _capacity;
    frontIndex = 0;
  }

 public:
  Queue() {}

  Queue(const size_t _capacity) { reserve(_capacity); }

  Queue(const Queue &other)
      : m_size(other.m_size), m_capacity(other.m_capacity) {
    arr = new T[m_capacity];
    for (int i = frontIndex; i < m_size - frontIndex; i++)
      arr[i] = other.arr[i];
  }

  Queue(Queue &&other) { swap(*this, other); }

  Queue(const std::initializer_list<T> &initList) {
    reserve(initList.size());
    for (const auto &element : initList) {
      push(element);
    }
  }

  // Capacity

  bool empty() const { return m_size - frontIndex == 0; }

  size_t size() const { return m_size - frontIndex; }

  // Element access

  T &front() { return arr[frontIndex]; }

  // Modifiers
  void push(const T &value) {
    if (m_size == m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    arr[m_size++] = value;
  }

  template <class... Args>
  void emplace(Args &&...args) {
    if (m_size == m_capacity) reserve(m_capacity == 0 ? 1 : m_capacity * 2);
    arr[m_size++] = T(std::forward<Args>(args)...);
  }

  void pop() {
    if (m_size - frontIndex == 0) return;
    arr[frontIndex].~T();
    ++frontIndex;
  }

  friend void swap(Queue &first, Queue &second) noexcept {
    using std::swap;
    swap(first.arr, second.arr);
    swap(first.m_size, second.m_size);
    swap(first.m_capacity, second.m_capacity);
    swap(first.frontIndex, second.frontIndex);
  }

  Queue &operator=(Queue other) {
    swap(*this, other);
    return *this;
  }

  void print() {
    for (size_t i = 0; i < size(); ++i) {
      std::cout << arr[(frontIndex + i) % m_capacity] << ' ';
    }
    std::cout << '\n';
  }

  ~Queue() { delete[] arr; }
};

int main() {
  using std::cout, std::endl;
  Queue<int> q;
  q.push(10);
  q.push(20);
  q.push(30);
  q.push(40);

  q.print();

  cout << "Queue size is " << q.size() << endl;
  cout << "Queue front is " << q.front() << endl;

  q.pop();
  cout << "Queue front is " << q.front() << endl;
  q.pop();
  cout << "Queue front is " << q.front() << endl;

  cout << "Queue size is " << q.size() << endl;
  q.print();

  Queue<int> q1{50, 100, 200, 400};
  cout << "Queue q1 using initializer list \n";
  q1.print();

  Queue<int> q2 = q;
  cout << "Queue q2 using operator = \n";
  q2.print();

  Queue<int> q3(q2);
  cout << "Queue q3\n";
  q3.print();

  return 0;
}