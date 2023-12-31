#include<iostream>
#include<cstring>
using std::cout;

class String {
private:
  char* ch;
  size_t sz;
  size_t cap;
  static int count;
public:
  String(): sz(0), cap(0) 
  {
    ++count;
  }
  
  String(int size):ch(new char[size]), sz(size), cap(size)
  {
    memset(ch, 0, sz);
    ++count;
  }
  String(int size, char symbol): ch(new char[size]), sz(size), cap(size) 
  {
    memset(ch, symbol, sz);
    ++count;
  }

  friend std::ostream& operator<<(std::ostream& out, const String& str) {
    for (char* i = str.ch; i != str.ch + str.sz; ++i) {
        out << *i;
    }
    out << '\n';
    return out;
  }

  void print() {
    for(char* i = ch; i !=ch+sz; i++) { 
      cout << *i;
    }
    cout << '\n';
  }
  
  //The copy-and-swap assignment
  String& operator=(String str) noexcept {
    std::swap(sz, str.sz);
    std::swap(ch, str.ch);
    return *this;
  }
  // Naive Method
  // String operator=(const String& str) { 
  //   //Guard self copy
  //   if(this == &str)
  //       return *this;
  //   
  //   if(sz != str.sz) {
  //     char* temp = new char[str.sz];
  //     delete[] ch;
  //     ch = temp;
  //     sz = str.sz;
  //   }
  //   std::copy(str.ch, str.ch + str.sz, ch);
  //   return *this;
  // }
  
  bool operator<(const String& str) {
    if(this->sz < str.sz) return true;
    return false;
  }
  
  bool operator>(const String& str) {
    if(this->sz > str.sz) return true;
    return false;
  }
  
  //bool operator<=

  // bool operator==(const String& str) {
  //   if(this->sz  str.sz)
  // }

  // String operator+(const String& str) {
  //
  // }
  
  int size() {
    return sz;
  }
  
  int capacity() {
    return cap;
  }

  bool empty() {
    if(sz == 0) return true;
    return false;
  }

  int find(char symbol) {
    for(int i = 0; i < sz; i++) {
      if(ch[i] == symbol) return i;
    }
    return -1;
  }

  static int getCount() {
    return count;
  }

  //void upper()
  //void lower()

  ~String()
  {
    delete[] ch;
    --count;
  }

};

int String::count = 0;

int main()
{
  String str(3, 'g');
  String str1(5, 'f');
  
  str.print();
  cout << (str < str1) << ' ' << (str1 > str) << ' ' << str.find('g') << '\n';
  
  cout << str << str1;
  cout << str.size() << ' ' << str.capacity() << std::endl;

  String str2;
  cout << "Str2 is empty: " << str.empty() << '\n'; // wrong
  
  str2 = (str);
  str2.print();

  cout << str.getCount() << std::endl;

  return 0;
}
