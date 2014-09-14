//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

#ifndef SVECTOR_H
	#define SVECTOR_H

#include <cassert>
#include <iostream>
#include <stdexcept>
#include <exception>
#include <vector>
#include <string>
#include <map>

using namespace std;

typedef map<string, int> simap;

class Whoops: public exception
{
  string error;
public:
  Whoops(const string &err);
  ~Whoops() throw();
  virtual const char* what() const throw();
}; // class Whoops

template <class T>
class SVector
{
  vector<T> values;
  simap indicies;
public:
  SVector(const int size);
  void push_back(string index, T value) throw(Whoops);
  void pop_back() throw(underflow_error);
  int operator[](string index) throw (range_error);
}; // class SVector

#include "SVector.cpp"

#endif // SVECTOR_H

