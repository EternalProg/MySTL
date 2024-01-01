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
    for(int i = 0; i < m_Size; ++i)
      m_Data[i] = other.m_Data[i];   
  }



//-------------------------Methods---------------------

  void push_back(const T& value) 
i  {
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

    m_Data[m_Size] = value;
    m_Size++;
  }

  void pop_back()
  {
  	
  }

  void emplace_back()
  {

  }

  --- begin()
  {

  }

  --- end()
  {

  }

  --- swap()
  {

  }

  --- assign(const int )
  {

  }

//------------------------Size------------------

  size_t size() const 
  {
    return m_Size;
  }

  size_t capacity() const
  {
    return m_Capacity;
  }

  void clear()
  {

  }

  bool empty() 
  {
    if(size == 0) return true;
    return false;
  }
  void reserve(size_t newCapacity)
  {
    if(newCapacity <= m_Capacity) return;

    newarr = reinterpret_cast<T*>(new byte[n * sizeof(T)]);

    for(size_t i = 0; i < m_Size; ++i)
    {
      new (newarr + i) T(arr[i]); //placement new
        //Using this syntax, we explicitly call the constructor at the given address
        // new (address) (type) initializer
        // Constructor T() at the address (newarr + 1)
        // from such parameters: arr[i]
        
        // newarr[i] = m_Data[i] -- Wrong
        // because it is not a fact that an object has been created at this address.
    }
    for(size_t i = 0; i < m_Size; ++i) 
    { 
      (m_Data + i)->~T();
    }
    delete[] reinterpret_cast<byte*>(m_Data);
    m_Data = newarr;
    m_Capacity = newCapacity;
  }

  void resize(size_t newSize, const T& value = T()) 
  {
    // 1. allocate a new block of memory
    // 2. cope/move old elements into a new block
    // 3. delete 
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

//-----------------Destructor------------------
  ~Vector()
  {
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
