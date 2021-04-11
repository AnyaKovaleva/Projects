#include "tasks.hpp"
#include <iostream>
#include <vector>

void taskThree()
{
  std::vector<int> dataVector;
  int temp = 0;
  while (std::cin >> temp && temp != 0)
  {
    dataVector.push_back(temp);
  }
  if (dataVector.empty() && std::cin.eof())
  {
    return;
  }
  if (std::cin.fail())
  {
    throw std::runtime_error("Reading has failed.\n");
  }
  if (temp != 0 && std::cin.eof())
  {
    throw std::invalid_argument("Invalid data.\n");
  }

  if (!dataVector.empty())
  {
    switch (dataVector.back())
    {
      case 1:
      {
        std::vector<int>::iterator iter = dataVector.begin();
        while (iter != dataVector.end())
        {
          if (*iter % 2 == 0)
          {
            iter = dataVector.erase(iter);
          }
          else
          {
            iter++;
          }
        }
        break;
      }

      case 2:
      {
        for (auto iter = dataVector.begin(); iter != dataVector.end(); iter++)
        {
          if (*iter % 3 == 0)
          {
            iter = dataVector.insert(++iter, 3, 1);
            iter += 2;
          }
        }
        break;
      }
      default:
        break;
    }
  }
  detail::print(dataVector);
}
