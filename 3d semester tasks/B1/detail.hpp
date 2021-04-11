#ifndef KOVALEVA_ANNA_A4_TEST_DETAIL_HPP
#define KOVALEVA_ANNA_A4_TEST_DETAIL_HPP

#include <iostream>
#include <cstddef>
#include <algorithm>
#include <stdexcept>
#include <functional>
#include <cstring>

namespace detail
{
  template<typename T>
  struct AccessWithIndex
  {
    using index_t = size_t;
    using value_type = typename T::reference;

    static value_type getElem(T& container, index_t index)
    {
      return container[index];
    }

    static index_t getBegin(const T&)
    {
      return 0;
    }

    static index_t getEnd(const T& container)
    {
      return container.size();
    }
  };

  template<typename T>
  struct AccessWithAt
  {
    using index_t = size_t;
    using value_type = typename T::reference;

    static value_type getElem(T& container, index_t index)
    {
      return container.at(index);
    }

    static size_t getBegin(const T&)
    {
      return 0;
    }

    static size_t getEnd(const T& container)
    {
      return container.size();
    }
  };

  template<typename T>
  struct AccessWithIterator
  {
    using index_t = typename T::iterator;
    using value_type = typename T::reference;

    static value_type getElem(T&, index_t index)
    {
      return *index;
    }

    static index_t getBegin(T& container)
    {
      return container.begin();
    }

    static index_t getEnd(T& container)
    {
      return container.end();
    }
  };

  template<template<typename C> class Traits, typename C>
  void
  sort(C& container, const std::function<bool(const typename C::value_type&, const typename C::value_type&)>& compare)
  {
    for (typename Traits<C>::index_t i = Traits<C>::getBegin(container); i != Traits<C>::getEnd(container); i++)
    {
      for (typename Traits<C>::index_t j = i; j != Traits<C>::getEnd(container); j++)
      {
        if (compare(Traits<C>::getElem(container, i), Traits<C>::getElem(container, j)))
        {
          std::swap(Traits<C>::getElem(container, i), Traits<C>::getElem(container, j));
        }
      }
    }
  }

  template<typename C>
  void print(const C& container)
  {
    for (auto count:container)
    {
      std::cout << count << ' ';
    }
    std::cout << "\n";
  }

  template<typename T> using SortType = std::function<bool(const T&, const T&)>;

  template<typename T>
  SortType<T> defineSortingType(const char *type)
  {
    const char *ascending = "ascending";
    const char *descending = "descending";
    if (strcmp(type, ascending) == 0)
    {
      return std::greater<T>();
    }
    else if (strcmp(type, descending) == 0)
    {
      return std::less<T>();
    }
    else
    {
      throw std::invalid_argument("Wrong sorting type");
    }
  }

}

#endif //KOVALEVA_ANNA_A4_TEST_DETAIL_HPP
