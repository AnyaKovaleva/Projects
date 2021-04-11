#include <stdexcept>
#include <iostream>
#include "DataStruct.hpp"
#include "usefulFunctions.hpp"

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  char comma = ',';
  int key1 = 0;
  int key2 = 0;

  in >> std::noskipws;
  in >> key1 >> skipWsExceptNewLine >> comma >> skipWsExceptNewLine;

  if (comma != ',' || key1 > 5 || key1 < -5)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  in >> std::noskipws;
  in >> key2 >> skipWsExceptNewLine >> comma;

  if (comma != ',' || key2 > 5 || key2 < -5)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  std::string str;
  std::getline(in >> skipWsExceptNewLine, str);

  if (str.empty())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  dataStruct = {key1, key2, str};

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  out << dataStruct.key1 << "," << dataStruct.key2 << "," << dataStruct.str;
  return out;
}

bool operator<(const DataStruct& first, const DataStruct& second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }
  return first.str.size() < second.str.size();
}


