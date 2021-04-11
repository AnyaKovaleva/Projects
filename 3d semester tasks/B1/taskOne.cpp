#include "tasks.hpp"
#include <iostream>
#include <vector>
#include <forward_list>
#include <stdexcept>
#include <functional>

void taskOne(const char *type)
{
  std::function<bool(int, int)> sortType = detail::defineSortingType<int>(type);
  std::vector<int> dataVector;
  int temp = 0;
  while (std::cin)
  {
    if (std::cin >> temp)
    {
      dataVector.push_back(temp);
    }
    else if (std::cin.eof())
    {
      break;
    }
    else
    {
      throw std::invalid_argument("Unexpected character");
    }
  }
  if (dataVector.empty() && std::cin.eof())
  {
    return;
  }

  std::vector<int> dataVector2(dataVector);
  std::forward_list<int> dataList(dataVector.begin(), dataVector.end());
  if (dataVector.size() > 1)
  {
    detail::sort<detail::AccessWithIndex>(dataVector, sortType);
    detail::sort<detail::AccessWithAt>(dataVector2, sortType);
    detail::sort<detail::AccessWithIterator>(dataList, sortType);
  }
  detail::print(dataVector);
  detail::print(dataVector2);
  detail::print(dataList);
}
