#include "tasks.hpp"
#include <random>
#include <functional>
#include <stdexcept>
#include <ctime>

namespace detail
{
  void fillRandom(double *array, int size)
  {
    if (array == nullptr)
    {
      throw std::invalid_argument("Array is empty");
    }
    if (size < 0)
    {
      throw std::invalid_argument("Size cannot be less than zero");
    }

    static std::mt19937 generator(static_cast<unsigned int>(time(0)));
    static std::uniform_real_distribution<double> distribution(-1.0, 1.0);
    for (int i = 0; i != size; i++)
    {
      array[i] = distribution(generator);
    }
  }
}

void taskFour(const char *type, int size)
{
  if (size <= 0)
  {
    throw std::invalid_argument("Incorrect size");
  }
  std::function<bool(double, double)> sortType = detail::defineSortingType<double>(type);

  std::vector<double> dataVector(size);
  detail::fillRandom(dataVector.data(), size);
  detail::print(dataVector);

  detail::sort<detail::AccessWithIndex>(dataVector, sortType);
  detail::print(dataVector);
}
