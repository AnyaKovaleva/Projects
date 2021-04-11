#include <iostream>
#include <stdexcept>
#include <cstdlib>

#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc == 1)
    {
      std::cerr << "Invalid number of arguments.";
      return 1;
    }
    switch (atoi(argv[1]))
    {
      case 1:
      {
        if (argc != 3)
        {
          std::cerr << "Invalid number of arguments.";
          return 1;
        }
        taskOne(argv[2]);
        break;
      }

      case 2:
      {
        if (argc != 3)
        {
          std::cerr << "Invalid number of arguments.";
          return 1;
        }
        taskTwo(argv[2]);
        break;
      }

      case 3:
      {
        if (argc != 2)
        {
          std::cerr << "Invalid number of arguments.";
          return 1;
        }
        taskThree();
        break;
      }

      case 4:
      {
        if (argc != 4)
        {
          std::cerr << "Invalid number of arguments.";
          return 1;
        }
        taskFour(argv[2], atoi(argv[3]));
        break;
      }

      default:
      {
        std::cerr << "Invalid arguments";
        return 1;
      }
    }
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what();
    return 1;
  }
  return 0;
}
