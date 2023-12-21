#include <iostream>
#include <stdexcept>
#include <cstring>
#include "str.h"

using namespace std;

// Add your implementations here.

Str::Str() {
  size_ = 0;
  //Str s() = "";
  data_ = new char[1];
  data_[0] = '\0';
}
Str::~Str() {
  delete [] data_;
}
Str::Str(const Str& s) {
  const char* string_ = s.data();
  int length = strlen(string_)+1;
  data_ = new char[length];
  strcpy(data_, string_);
  size_ = strlen(data_);
  // constructor for string of type Str
  // appending the null character to the end
}

Str::Str(const char* s) {
  if (s == NULL) {
    //size_ = 0;
    data_ = new char[1];
    // s is just null character so append null
    *data_ = '\0';
    return;
  }
  // else data is shallow copy of s 
  data_ = new char[strlen(s)+1];
  strcpy(data_, s);
  size_ = strlen(data_);
}
ostream& operator<<(ostream& ostr, const Str& s) {
  // using namespace std so do we have toi do
  // std::ostream&
  ostr << s.data_;
  return ostr;
}
size_t Str::size() const {
  // return size of string
  return size_;
}
Str& Str::operator=(const Str& s) {
  // assignment operator  
  if (&s == this) {
    return *this;
  }
  const char* new_string = s.data();
  delete [] data_;
  int length = strlen(new_string)+1;
  data_ = new char[length];
  strcpy(data_, new_string);
  size_ = strlen(data_);
  return *this;

}
Str& Str::operator=(const char* s) {
  // assignment operator
  if (s == NULL) {
    // make it the null character
    data_ = new char[1];
    data_[0] = '\0';
    return *this;
  }
  // delete anything in data
  delete [] data_;
  int length = strlen(s)+1;
  // length of the string that we are trying to assign to s 
  data_ = new char[length];
  // data is now length of s
  strcpy(data_,s);
  // shallow copy s contents into data which is empty
  size_ = strlen(data_);
  return *this;

}
bool Str::operator!=(const Str &rhs) const {
  if (strcmp(data_,rhs.data_)) {
    return true;
  }
  else {
    return false;
  }

}
bool Str::operator==(const Str &rhs) const {
  if (*this != rhs) {
    return false;
  }
  else {
    return true;
  }
}
Str& Str::operator+=(const Str& s) {
  // string concat assignment operator
  int total_len = strlen(data_) + strlen(s.data_);
  char* new_str = new char[total_len+1];
  strcpy(new_str, data_);
  // copy data into new string
  strcat(new_str,s.data_);
  // append s data into the new string
  size_ = total_len;
  delete [] data_;
  data_ = new_str;
  return *this;
}

Str& Str::operator+=(const char* s) {
  //Char. array concatenation-assignment operator
  // If s is NULL simply return this Str
  if (s == NULL) {
    return *this;
  }
  int total_len = strlen(data_) + strlen(s);
  char* new_str = new char[total_len+1];
  strcpy(new_str, data_);
  // copy data into new string
  strcat(new_str,s);
  // append s data into the new string
  size_ = total_len;
  delete [] data_;
  data_ = new_str;
  return *this;

}
Str Str::operator+(const Str& rhs) const {
  // string concat operator
  //E.g. str s1("a"), s2("b"); cout << s1 + s2 << endl;
  Str temp(*this);
  temp += rhs;
  return temp;
}
Str Str::operator+(const char* rhs) const {
  // string concat operator
  //E.g. str s1; cout << s1 + " world" << endl;
  // If rhs is NULL, simply return a copy of this Str
  Str temp(*this);
  temp += rhs;
  return temp;
}

// Given implementations - DO NOT ALTER
const char* Str::data() const
{
  return data_;
}

char& Str::operator[](unsigned int i)
{
  if(i >= size_ ){
    throw std::out_of_range("Index is out of range");
  }
  return data_[i];
}

char const & Str::operator[](unsigned int i) const
{
  if(i >= size_ ){
    throw std::out_of_range("Index is out of range");
  }
  return data_[i];
}

bool Str::operator<(const Str &rhs) const
{
  return (strcmp(data_, rhs.data_) < 0);
}

bool Str::operator>(const Str &rhs) const
{
  return (strcmp(data_, rhs.data_) > 0);
}

std::istream& operator>>(std::istream& istr, Str& s)
{
  std::string stemp;
  istr >> stemp;
  s = stemp.c_str();
  return istr;
}

