#include <iostream>
#include <cassert>

template <typename T>
class Vector 
{
private:
  T* m_Data = nullptr;
  size_t m_Size = 0;
  size_t m_Capacity = 0;

public:
//-------------------------Constructor-----------------
  Vector() 
  {
  }
  
  Vector(const size_t size, const T& value = T())
  {
    resize(size, value);
  }

  Vector(const Vector<T>& other)
    :m_Size(other.m_Size), m_Capacity(other.m_Capacity)
  {
    m_Data = new T[m_Capacity];
    for(int i = 0; i < m_Size; ++i)
      m_Data[i] = other.m_Data[i];   
  }

  Vector(std::initializer_list<T> initList)   
  {
    reserve(initList.size());
    for (const auto& element : initList) {
        emplace_back(element);
    }
  }



//-------------------------Methods---------------------

  void push_back(const T& value) 
  {
    if(m_Size == m_Capacity) 
    {   
      resize(m_Capacity + m_Capacity / 2); 
    }

    new (m_Data+m_Size) T(value);
    ++m_Size;
  }

  void emplace_back(const T& value) 
  {
    if(m_Size >= m_Capacity)
    {
      resize(m_Capacity + m_Capacity / 2);
    }

    new (m_Data+m_Size) T(value);
    m_Size++;
  }

  void pop_back()
  {
    if (m_Size > 0) {
        --m_Size;
    }
  }


  T* begin()
  {
    return m_Data;
  }

  T* end()
  {
    return m_Data + m_Size;
  }

  void swap(Vector<T>& other)
  {
    std::swap(m_Data, other.m_Data);
    std::swap(m_Size, other.m_Size);
    std::swap(m_Capacity, other.m_Capacity);
  }

  void assign(const size_t size, const T& value)
  {
    if(m_Capacity < size)
    {
      resize(size,value);
    } 
    else 
    {
      for(size_t i = 0; i < size; ++i)
      {
        m_Data[i] = value;
      }
      m_Size = size;
  }

//------------------------Size------------------

  size_t size() const noexcept 
  {
    return m_Size;
  }

  size_t capacity() const noexcept
  {
    return m_Capacity;
  }

  void clear()
  {
    for(int i = 0; i < m_Size; ++i) {
      m_Data[i].~T();
    }
    m_Size = 0;
  }

  bool empty() const noexcept
  {
    return m_Size == 0;
  }

  void reserve(size_t newCapacity)
  {
    if(newCapacity <= m_Capacity) return;

    newarr = reinterpret_cast<T*>(new byte[n * sizeof(T)]);
    
    //size_t i = 0;
    
    try {
      std::uninitialized_copy(m_Data, m_Data+m_Size, newarr);
    } catch(...) {
      delete[] reinterpret_cast<byte*>(newarr);
      throw;
    }

    /*try {
      for(; i < m_Size; ++i)
      {
        new (newarr + i) T(arr[i]); //placement new
        //Using this syntax, we explicitly call the constructor at the given address
        // new (address) (type) initializer
        // Constructor T() at the address (newarr + 1)
        // from such parameters: arr[i]
        
        // newarr[i] = m_Data[i] -- Wrong
        // because it is not a fact that an object has been created at this address.
      }
    } catch (...) {
        for(size_t j = 0; j < i; ++j) {
          (newarr+i)->~T();
        }
        delete[] reinterpret_cast<byte*>(newarr);
        throw;
    }
    for(size_t i = 0; i < m_Size; ++i) 
    { 
      (m_Data + i)->~T();
    }
    delete[] reinterpret_cast<byte*>(m_Data);
    m_Data = newarr;*/
    m_Capacity = newCapacity;
  }

  void resize(size_t newSize, const T& value = T()) 
  {
    if(newSize > m_Capacity) reserve(newSize);

    for(size_t i = m_Size; i < newSize; i++)
    {
      new (m_Data+i) T(value);
    }
    if(newSize < m_Size) m_Size = newSize;
  }

//---------------Operator-----------------------

  const T& operator[](size_t index) const
  {
    assert(index >= 0 && index < m_Size);

    return m_Data[index];
  } 
  
  T& operator[](size_t index) 
  {
    assert(index >= 0 && index < m_Size);

    return m_Data[index];
  }

  Vector<T>& operator=(Vector<T> other)
  {
    /*
    if(this == &other)
        return *this;
    if(m_Size != other.m_Size)
      resize(other.m_Size);
    
    std::copy(other.m_Data, other.m_Data + other.m_Size, m_Data);
    return *this;
    */
    swap(*this,other); 
    return *this;
  }

  Vector<T>& operator+=(const Vector<T>& other)
  {
    auto end = m_Data+m_Size;
    if(m_Capacity < m_Size + other.m_Size) 
    {
      resize(m_Size+other.m_Size);
    }
    
    std::copy(other.m_Data, other.m_Data+other.m_Size, end);
    return *this;
  }

  friend Vector<T> operator+(Vector<T> lhs, const Vector<T>& rhs)
  {
    lhs += rhs;
    return lhs;
  }

  friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
  {
    if(lhs.m_Size != rhs.m_Size) return false;

    for(int i = 0; i < lhs.m_Size; ++i)
    {
      if(lhs.m_Data[i] != rhs.m_Data[i]) return false;
    }
    return true;
  }



//-----------------Destructor------------------
  ~Vector()
  {
    if(m_Data)
        delete[] m_Data;
  }
};

template<typename T>
void PrintVector(const Vector<T>& v) 
{
  for(auto i = 0; i < v.size(); i++) 
  {
    std::cout << v[i] << '\n';
  }

  std::cout << "----------------------" << '\n';
}
/*
class Test {
private:
  int m_x = 0;
  int m_y = 0;
  int m_z = 0;
public:
  Test()
  {
  }

  Test(int x, int y, int z)
    : m_x(x), m_y(y), m_z(z)
  {:
  }

  Test(const Test& other)
    :m_x(other.m_x), m_y(other.m_y), m_z(other.m_z) 
  {
  }

};*/

int main()
{
  Vector<std::string> v;
  
  v.push_back("C++");
  v.push_back("STL");
  v.push_back("VECTOR");
  
  PrintVector(v);

  v.push_back()
}
