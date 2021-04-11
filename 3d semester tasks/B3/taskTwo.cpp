#include "tasks.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>
#include "factorialContainer.hpp"

void taskTwo()
{
  FactorialContainer factorialContainer(1, 10);
  std::copy(factorialContainer.begin(), factorialContainer.end(),
            std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";
  std::reverse_copy(factorialContainer.begin(), factorialContainer.end(),
                    std::ostream_iterator<size_t>(std::cout, " "));
  std::cout << "\n";
}

