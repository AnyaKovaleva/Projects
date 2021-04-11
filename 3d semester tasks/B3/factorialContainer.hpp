#ifndef KOVALEVA_ANNA_B3_FACTORIALCONTAINER_HPP
#define KOVALEVA_ANNA_B3_FACTORIALCONTAINER_HPP

#include <iterator>

class FactorialContainer
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, unsigned, unsigned, const unsigned *, unsigned>
  {
  public:
    Iterator();

    Iterator(const size_t index);

    Iterator& operator++();

    Iterator operator++(int);

    Iterator& operator--();

    Iterator operator--(int);

    const size_t& operator*();

    bool operator==(const Iterator& other) const;

    bool operator!=(const Iterator& other) const;

  private:
    size_t index_;
    size_t value_;

    size_t factorial(const size_t num) const;
  };

  FactorialContainer(const size_t min, const size_t max);

  Iterator begin() const;

  Iterator end() const;

private:
  size_t min_;
  size_t max_;
};

#endif //KOVALEVA_ANNA_B3_FACTORIALCONTAINER_HPP
