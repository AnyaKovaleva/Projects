#ifndef KOVALEVA_ANNA_B2_QUEUEWITHPRIORITY_HPP
#define KOVALEVA_ANNA_B2_QUEUEWITHPRIORITY_HPP

#include <list>

template<typename T>
class QueueWithPriority
{
public:
  enum ElementPriority
  {
    LOW,
    NORMAL,
    HIGH
  };

  void add(const T& data, const ElementPriority& priority);

  bool isEmpty() const noexcept;

  template<typename Handler>
  int handle(const Handler& handler);

  void accelerate();

private:
  std::list<T> lowPriority_;
  std::list<T> normalPriority_;
  std::list<T> highPriority_;
};

template<typename T>
void QueueWithPriority<T>::add(const T& data, const QueueWithPriority::ElementPriority& priority)
{
  switch (priority)
  {
    case LOW:
      lowPriority_.push_back(data);
      break;
    case NORMAL:
      normalPriority_.push_back(data);
      break;
    case HIGH:
      highPriority_.push_back(data);
      break;
  }
}

template<typename T>
bool QueueWithPriority<T>::isEmpty() const noexcept
{
  return lowPriority_.empty() && normalPriority_.empty() && highPriority_.empty();
}

template<typename T>
template<typename Handler>
int QueueWithPriority<T>::handle(const Handler& handler)
{
  if (isEmpty())
  {
    return 1;
  }

  int error = 0;
  if (!highPriority_.empty())
  {
    error = handler(highPriority_.front());
    highPriority_.pop_front();
    return error;
  }
  else if (!normalPriority_.empty())
  {
    error = handler(normalPriority_.front());
    normalPriority_.pop_front();
    return error;
  }
  else
  {
    error = handler(lowPriority_.front());
    lowPriority_.pop_front();
    return error;
  }

}

template<typename T>
void QueueWithPriority<T>::accelerate()
{
  highPriority_.splice(highPriority_.end(), lowPriority_);
}

#endif //KOVALEVA_ANNA_B2_QUEUEWITHPRIORITY_HPP
