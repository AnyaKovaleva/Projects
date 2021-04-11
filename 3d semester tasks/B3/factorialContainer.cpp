#include "factorialContainer.hpp"

FactorialContainer::Iterator::Iterator() :
  index_(1),
  value_(1)
{ }

FactorialContainer::Iterator::Iterator(size_t index) :
  index_(index),
  value_(factorial(index))
{ }

FactorialContainer::Iterator& FactorialContainer::Iterator::operator++()
{
  value_ *= ++index_;
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator++(int)
{
  Iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::Iterator& FactorialContainer::Iterator::operator--()
{
  if (index_ > 1)
  {
    value_ /= index_--;
  }
  return *this;
}

FactorialContainer::Iterator FactorialContainer::Iterator::operator--(int)
{
  Iterator temp = *this;
  --(*this);
  return temp;
}

const size_t& FactorialContainer::Iterator::operator*()
{
  return value_;
}

bool FactorialContainer::Iterator::operator==(const FactorialContainer::Iterator& other) const
{
  return ((index_ == other.index_) && (value_ == other.value_));
}

bool FactorialContainer::Iterator::operator!=(const FactorialContainer::Iterator& other) const
{
  return !(*this == other);
}

size_t FactorialContainer::Iterator::factorial(size_t num) const
{
  size_t factorial = 1;
  for (size_t i = 1; i <= num; i++)
  {
    factorial *= i;
  }
  return factorial;

}

FactorialContainer::FactorialContainer(size_t min, size_t max) :
  min_(min),
  max_(++max)
{ }

FactorialContainer::Iterator FactorialContainer::begin() const
{
  return FactorialContainer::Iterator(min_);
}

FactorialContainer::Iterator FactorialContainer::end() const
{
  return FactorialContainer::Iterator(max_);
}





