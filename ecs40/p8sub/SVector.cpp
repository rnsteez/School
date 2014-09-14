//Authors: Christopher Chen (997549548), Wai Shing Yung (996936848)
//"Live by the code, die by the code."

using namespace std;

Whoops::Whoops(const string &err) : error(err)
{
  
} // Whoops()


Whoops::~Whoops() throw()
{
  
} // ~Whoops()


const char* Whoops::what() const throw()
{
  return error.c_str();
} // what()


template <class T>
SVector<T>::SVector(const int size) : values(vector<T>(size))
{
  values.clear();
} // SVector()


template <class T>
void SVector<T>::push_back(string index, T value) throw(Whoops)
{
  assert (indicies.find(index) == indicies.end());
  if (indicies.find(index) != indicies.end())
    throw Whoops(index);
  values.push_back(value);
  indicies[index] = values.size() - 1;
} // push_back()


template <class T>
void SVector<T>::pop_back() throw(underflow_error)
{
  assert (values.size() != 0);
  if (!values.size())
    throw underflow_error("Underflow error");

  values.pop_back();
  for(simap::iterator itr = indicies.begin(); itr != indicies.end(); itr++)
  {
    if (itr->second == (int) values.size())
    {
      indicies.erase(itr);
      break;
    }
  }
} // pop_back()


template <class T>
int SVector<T>::operator[](string index) throw (range_error)
{
  simap::iterator itr = indicies.find(index);
  assert (itr != indicies.end());
  if (itr == indicies.end())
    throw range_error(index);
  return (values[itr->second]);
} // operator[]()