#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include "DataStruct.hpp"

int main()
{
  std::vector<DataStruct> dataStructVector((std::istream_iterator<DataStruct>(std::cin)),
                                           std::istream_iterator<DataStruct>());

  try
  {
    if (std::cin.bad())
    {
      std::cerr << "Input stream error\n";
      return 1;
    }

    if (!std::cin.eof())
    {
      std::cerr << "Incorrect input data\n";
      return 1;
    }

    std::sort(dataStructVector.begin(), dataStructVector.end());
    std::copy(dataStructVector.begin(), dataStructVector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }

  return 0;
}


