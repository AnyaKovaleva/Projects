#include "tasks.hpp"

#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>
#include "bookmark.hpp"
#include "commands.hpp"

void taskOne()
{
  Bookmark bookInterface;

  using iterator = std::istream_iterator<std::function<void(Bookmark& phoneBook, std::ostream& output)>>;
  std::for_each(iterator(std::cin), iterator(), [&](auto& function)
  {
    function(bookInterface, std::cout);
  });
  if (!std::cin.eof())
  {
    throw std::runtime_error("Error while reading!");
  }
}


