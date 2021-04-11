#include "phoneBook.hpp"

#include <algorithm>
#include <iostream>
#include <string>
#include "usefulFunctions.hpp"

PhoneBook::iterator PhoneBook::insertAfter(const_iterator iterator1, const Contact& contact)
{
  if (contactsList_.empty())
  {
    return contactsList_.insert(contactsList_.begin(), contact);
  }
  else
  {
    return contactsList_.insert(std::next(iterator1), contact);
  }
}

PhoneBook::iterator PhoneBook::insertBefore(const_iterator iterator1, const Contact& contact)
{
  return contactsList_.insert(iterator1, contact);
}

PhoneBook::iterator PhoneBook::move(iterator iterator1, int step)
{
  if (step >= 0)
  {
    while ((std::next(iterator1) != contactsList_.end()) && (step > 0))
    {
      iterator1 = std::next(iterator1);
      step--;
    }
  }
  else
  {
    if (step < 0)
    {
      while ((std::next(iterator1) != contactsList_.begin()) && (step < 0))
      {
        iterator1 = std::prev(iterator1);
        step++;
      }
    }
  }
  return iterator1;
}

PhoneBook::iterator PhoneBook::begin() noexcept
{
  return contactsList_.begin();
}

PhoneBook::iterator PhoneBook::end() noexcept
{
  return contactsList_.end();
}

PhoneBook::iterator PhoneBook::erase(iterator iterator1)
{
  if (contactsList_.empty())
  {
    return contactsList_.end();
  }
  else
  {
    return contactsList_.erase(iterator1);
  }
}

bool PhoneBook::isEmpty() const
{
  return contactsList_.empty();
}

void PhoneBook::pushBack(const Contact contact)
{
  return contactsList_.push_back(contact);
}

std::istream& operator>>(std::istream& in, PhoneBook::Contact& contact)
{
  std::string phoneNumber;
  in >> skipWsExceptNewLine >> std::noskipws >> phoneNumber;

  if (phoneNumber.empty())
  {
    in.setstate(std::ios_base::failbit);
  }
  if (!std::all_of(phoneNumber.begin(), phoneNumber.end(), [](auto& digit)
  {
    return isdigit(digit);
  }))
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios_base::failbit);
    return in;
  }

  char ch = '0';
  std::string name;
  in >> skipWsExceptNewLine;

  if (in.get() != '\"')
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios_base::failbit);
    return in;
  }

  ch = static_cast<char>(in.get());
  std::ios_base::iostate inState = in.rdstate();

  while (ch != '\n' && !in.eof())
  {
    if (ch == '\\')
    {
      ch = static_cast<char>(in.get());
      if (ch != '\\' && ch != '\"')
      {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in.setstate(std::ios_base::failbit);
        return in;
      }
    }
    else if (ch == '\"')
    {
      ch = static_cast<char>(in.get());
      if (ch != '\n' && !in.eof())
      {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        in.setstate(std::ios_base::failbit);
        return in;
      }
      if (in.eof())
      {
        in.clear();
        in.setstate(inState);
      }
      break;
    }
    name += ch;

    ch = static_cast<char>(in.get());
  }

  if (name.empty())
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    in.setstate(std::ios_base::failbit);
    return in;
  }

  contact.name_ = name;
  contact.phoneNumber_ = phoneNumber;

  return in;
}

std::ostream& operator<<(std::ostream& out, PhoneBook::Contact& contact)
{
  std::cout << contact.phoneNumber_ << " " << contact.name_ << "\n";
  return out;
}
