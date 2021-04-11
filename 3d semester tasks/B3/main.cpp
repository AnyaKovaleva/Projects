#include <iostream>
#include <stdexcept>
#include <string>

#include "tasks.hpp"

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Incorrect parameters\n";
    return 1;
  }

  int taskNumber = std::stoi(argv[1]);
  switch (taskNumber)
  {
    case 1:
      try
      {
        taskOne();
      }
      catch (const std::exception& exception)
      {
        std::cerr << exception.what();
        return 2;
      }
      break;
    case 2:
      taskTwo();
      break;
    default:
      std::cerr << "Invalid task number\n";
      return 1;
  }

  return 0;
}

