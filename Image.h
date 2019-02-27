#ifndef IMAGE_H
#define IMAGE_H
#include <iostream>
#include <memory>
#include <string>
#include <sstream>
#include <fstream>
#include <tr1/unordered_map>
#include <bits/stdc++.h>
using namespace std::tr1;
using namespace std;
namespace NKNPET001{
class Image{

  private:
    int width, height;
    string header;
    string image_name;
    std::unique_ptr<unsigned char[]> data;

  public:
  // empty constructor
  Image();
  // constructor with file name
  Image(const char* name);
  // copy constructor
  Image(const Image& rhs);
  // move constructor
  Image(Image&& rhs);
  // destructor
  ~Image();
  
  void load(string name);
  void save(std::unique_ptr<unsigned char[]> &array, string name);
  void setimage_name(string temp);
  class iterator
    { friend Image;
      private:
      unsigned char *ptr;
      // construct only via Image class (begin/end)
      iterator(u_char *p) : ptr(p) {}
      public:
      //copy construct is public
      iterator( const iterator & rhs) : ptr(rhs.ptr) {}
      // define overloaded ops: *, ++, --, =
      iterator & operator=(const iterator & rhs) // overloading assignment operator
      {
        if(this != &rhs){
          this->ptr = rhs.ptr;
          }
        return *this;
      }
      iterator& operator++(){ //overloading iterator pre-increment
        ptr++;
        return *this;
      }
      iterator operator++(int){  // overloading iterator post-increment 
        iterator temp = *this;
        ++*this;
        return temp;
      }
     bool operator == (iterator &temp){ // overloading iterator equality check
       return (ptr == temp.ptr);
     }
     bool operator != (const iterator &temp)const{  //overloading not equal to check
       return (ptr != temp.ptr);
     }
     unsigned char& operator *()const{  // overloading dereferencing method
       return *(ptr) ;
     }
      // other methods for iterator
     
    iterator & operator=(iterator && rhs){ // overloading move assignment operator
      if(this != &rhs){
          this->ptr = std::move(rhs.ptr);
          rhs.ptr = nullptr;
      }
      return *this;
    }
     
      iterator(iterator && rhs) : ptr(rhs.ptr)  // overloading move constructor
        {rhs.ptr = nullptr;}
     
     iterator operator--(const int){  // overloading iterator post-decrement
      iterator temp(*this);
      this->ptr -= 1;
      return temp;
     }
     
     iterator & operator--(){   // overloading iterator pre-decrement
      this->ptr -= 1;
      return *this;
     }
    };
  
    // define begin()/end() to get iterator to start and
    // "one-past" end.
    iterator begin(void) { return iterator(data.get());} // etc
    iterator end(void) {return iterator(data.get()+(width*height));}
    
  // image addition overloading  
  std::unique_ptr<unsigned char[]> operator+(Image& rhs);
  
  // image subtraction overloading
  std::unique_ptr<unsigned char[]> operator-(Image& rhs);
  
  // image invert overloading
  std::unique_ptr<unsigned char[]> operator!();

  // image masking overloading
  std::unique_ptr<unsigned char[]> operator/(Image& rhs);
  
  // image threshold overloading
  std::unique_ptr<unsigned char[]> operator*(int rhs);
  
  // image >> operator overloading
  Image& operator>>(const char* name);
  
  // image << operator overloading
  Image& operator<<(const char* name);
  
  // image move operator overloading
  Image& operator=(Image&& rhs);
  
  // image copy operator overloading
  Image& operator=(const Image& rhs);
  
};
}
#endif
