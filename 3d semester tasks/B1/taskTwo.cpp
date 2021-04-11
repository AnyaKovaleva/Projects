#include "tasks.hpp"
#include <vector>
#include <iostream>
#include <cstddef>
#include <memory>

const size_t MAXSIZEOFBUFFER = 1024;

void taskTwo(const char *fileName)
{
  if (fileName == nullptr)
  {
    throw std::invalid_argument("Empty file name");
  }

  std::ifstream file(fileName);
  if (!file)
  {
    throw std::runtime_error("Couldn't open the file");
  }

  size_t size = MAXSIZEOFBUFFER;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char *>(malloc(size)), &free);
  size_t index = 0;
  while (file)
  {
    file.read(&array[index], MAXSIZEOFBUFFER);
    index += file.gcount();
    if (file.gcount() == MAXSIZEOFBUFFER)
    {
      size += MAXSIZEOFBUFFER;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char *>(realloc(array.get(), size)), &free);
      if (!temp)
      {
        file.close();
        throw std::runtime_error("Failed to reallocate memory");
      }
      array.release();
      std::swap(array, temp);
    }
  }
  std::vector<char> dataVector(array.get(), array.get() + index);
  for (char i : dataVector)
  {
    std::cout << i;
  }
  file.close();
}
