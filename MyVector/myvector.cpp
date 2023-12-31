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
    resize(2);
  }

//-------------------------Methods---------------------

  void push_back(const T& value) 
i  {
    if(m_Size == m_Capacity) 
    {   
      resize(m_Capacity + m_Capacity / 2); 
    }

    m_Data[m_Size] = value;
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
      
  }

  void resize(size_t newSize, const T& value = T()) 
  {
    // 1. allocate a new block of memory
    // 2. cope/move old elements into a new block
    // 3. delete 

    T* newBlock = new T[newCapacity];
    
    if(newCapacity < m_Size) 
    {
      m_Size = newCapacity;
    }

    for(size_t i = 0; i < m_Size; i++) 
    {
      newBlock[i] = std::move(m_Data[i]); 
    }
    

    delete[] m_Data;
    m_Data = newBlock;
    m_Capacity = newCapacity;

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