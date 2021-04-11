#include <iostream>
#include <stdexcept>
#include <cstdlib>

void taskOne(std::istream& in, std::ostream& out);

void taskTwo(std::istream& in, std::ostream& out);

int main(int argc, char *argv[])
{
  try
  {
    if (argc == 2)
    {
      int task = atoi(argv[1]);

      switch (task)
      {
        case 1:
          taskOne(std::cin, std::cout);
          break;
        case 2:
          taskTwo(std::cin, std::cout);
          break;
        default:
          std::cerr << "Incorrect task number";
          return 1;
      }
    }
    else
    {
      std::cerr << "Wrong number of parameters";
      return 1;
    }
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what();
    return 1;
  }
  return 0;
}
