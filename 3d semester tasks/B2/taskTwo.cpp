#include <list>
#include <stdexcept>
#include "tasks.hpp"

const int MAX = 20;
const int MAX_SIZE = 20;
const int MIN = 1;

void taskTwo(std::istream& in, std::ostream& out)
{
  std::list<int> list{};
  int num = 0;

  while (in >> num)
  {
    if (num < MIN || num > MAX)
    {
      throw std::invalid_argument("Incorrect number");
    }
    list.push_back(num);
  }
  if (!in.eof())
  {
    throw std::invalid_argument("Error while reading");
  }

  if (list.size() > MAX_SIZE)
  {
    throw std::invalid_argument("Number of elements in a list must be less than 20");
  }

  for (auto i = list.begin(), j = list.end(); i != j--; i++)
  {
    if (i == j)
    {
      out << *i << "\n";
      return;
    }
    out << *i << " " << *j << " ";
  }
  out << "\n";
}
