#include <cassert>
#include <cstdlib>
#include <iostream>
#include <memory>

template <typename T>
class Vector {
 private:
  T *m_Data = nullptr;
  size_t m_Size = 0;
  size_t m_Capacity = 0;

 public:
  //-------------------------Constructor-----------------
  Vector() {}

  Vector(const size_t size, const T &value = T()) { resize(size, value); }

  Vector(const Vector<T> &other)
      : m_Size(other.m_Size), m_Capacity(other.m_Capacity) {
    m_Data = new T[m_Capacity];
    for (int i = 0; i < m_Size; ++i) m_Data[i] = other.m_Data[i];
  }

  Vector(const std::initializer_list<T>& initList) {
    reserve(initList.size());
    for (const auto &element : initList) {
      push_back(element);
    }
  }

  //-------------------------Methods---------------------

  void push_back(const T &value) {
    if (m_Size == m_Capacity) {
        reserve(m_Capacity + m_Capacity / 2 + 1);
    }

    new (m_Data + m_Size) T(value);
    ++m_Size;
}

  void emplace_back(T&& value) {
    if (m_Size >= m_Capacity) {
        reserve(m_Capacity + m_Capacity / 2 + 1);
    }

    new (m_Data + m_Size) T(std::move(value));
    m_Size++;
}

  void pop_back() {
    if (m_Size > 0) {
      --m_Size;
      (m_Data + m_Size)->~T();
    }
  }

  T* begin() { return m_Data; }

  T* end() { return m_Data + m_Size; }

  void swap(Vector<T> &other) {
    std::swap(m_Data, other.m_Data);
    std::swap(m_Size, other.m_Size);
    std::swap(m_Capacity, other.m_Capacity);
  }

  void assign(const size_t size, const T &value) {
    if (m_Capacity < size) {
      resize(size, value);
    } else {
      for (size_t i = 0; i < size; ++i) {
        m_Data[i] = value;
      }
      m_Size = size;
    }
  }

  //------------------------Size------------------

  size_t size() const noexcept { return m_Size; }

  size_t capacity() const noexcept { return m_Capacity; }

  void clear() {
    for (size_t i = 0; i < m_Size; ++i) {
        m_Data[i].~T();
    }
    delete[] reinterpret_cast<int8_t*>(m_Data);
    m_Data = nullptr;
    m_Size = 0;
    m_Capacity = 0;
  }

  bool empty() const noexcept { return m_Size == 0; }

  void reserve(size_t newCapacity) {
    if (newCapacity <= m_Capacity) return;

    auto newarr = reinterpret_cast<T *>(new int8_t[newCapacity * sizeof(T)]);
    try {
      std::uninitialized_copy(m_Data, m_Data + m_Size, newarr);
    } catch (...) {
      delete[] reinterpret_cast<int8_t *>(newarr);
      throw;
    }

    for (size_t i = 0; i < m_Size; ++i) {
      (m_Data + i)->~T();
    }
    delete[] reinterpret_cast<int8_t *>(m_Data);
    m_Data = std::move(newarr);
    m_Capacity = newCapacity;
  }

  void resize(size_t newSize, const T &value = T()) {
    if (newSize > m_Capacity) reserve(newSize);

    for (size_t i = m_Size; i < newSize; i++) {
      new (m_Data + i) T(std::move(value));
    }
    if (newSize < m_Size) m_Size = newSize;
  }

  //---------------Operator-----------------------

  const T &operator[](size_t index) const { return m_Data[index]; }

  T &operator[](size_t index) { return m_Data[index]; }
  T &at(size_t index) {
    assert(index >= 0 && index < m_Size);
    return m_Data[index];
  }

  Vector<T> &operator=(Vector<T> other) {
    /*
    if(this == &other)
        return *this;
    if(m_Size != other.m_Size)
      resize(other.m_Size);

    std::copy(other.m_Data, other.m_Data + other.m_Size, m_Data);
    return *this;
    */
    swap(*this, other);
    return *this;
  }

  Vector<T> &operator+=(const Vector<T> &other) {
    auto end = m_Data + m_Size;
    if (m_Capacity < m_Size + other.m_Size) {
      resize(m_Size + other.m_Size);
    }

    std::copy(other.m_Data, other.m_Data + other.m_Size, end);
    return *this;
  }

  friend Vector<T> operator+(Vector<T> lhs, const Vector<T> &rhs) {
    lhs += rhs;
    return lhs;
  }

  friend bool operator==(const Vector<T> &lhs, const Vector<T> &rhs) {
    if (lhs.m_Size != rhs.m_Size) return false;

    for (int i = 0; i < lhs.m_Size; ++i) {
      if (lhs.m_Data[i] != rhs.m_Data[i]) return false;
    }
    return true;
  }

  //-----------------Destructor------------------
  ~Vector() {
    for (size_t i = 0; i < m_Size; ++i) {
        m_Data[i].~T();
    }
    delete[] reinterpret_cast<int8_t*>(m_Data);
  }
};

template <typename T>
void PrintVector(const Vector<T> &v) {
  for (auto i = 0; i < v.size(); i++) {
    std::cout << v[i] << '\n';
  }

  std::cout << "----------------------" << '\n';
}

int main() {
  using std::endl, std::cout;
  Vector<std::string> v;
  
  v.push_back("C++");
  v.push_back("STL");
  v.push_back("VECTOR");

  PrintVector(v);

  if (!v.empty()) {
    cout << "Vector v is not empty and his size is: " << v.size() << endl;
  }
  cout << "Vector v capacity " << v.capacity() << endl;

  v.resize(10);
  cout << "Vector v size after resize " << v.size() << endl;
  cout << "Vector v capacity after reserve " << v.capacity() << endl;

  cout << "Vector v end " << v.end() << endl;

  v.pop_back();
  cout << "Result of using pop_back: " << endl;
  PrintVector(v);

  Vector<std::string> v1{"never", "give", "up"};
  v.swap(v1);
  cout << "Vector v after swap with v1:" << endl;
  PrintVector(v);

  v1.assign(3, "something");
  cout << "v1 after assign methods: " << endl;
  PrintVector(v1);

  v.clear();
  if (v.empty()) cout << "Now vector v1 is empty!!!" << endl;

  return 0;
}
