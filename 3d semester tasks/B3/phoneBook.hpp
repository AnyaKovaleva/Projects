#ifndef KOVALEVA_ANNA_B3_PHONEBOOK_HPP
#define KOVALEVA_ANNA_B2_PHONEBOOK_HPP

#include <string>
#include <list>
#include <iostream>

class PhoneBook
{
public:
  struct Contact
  {
    std::string name_;
    std::string phoneNumber_;
  };
  using iterator = std::list<Contact>::iterator;
  using const_iterator = std::list<Contact>::const_iterator;

  iterator insertAfter(const_iterator iterator1, const Contact& contact);

  iterator insertBefore(const_iterator iterator1, const Contact& contact);

  iterator move(iterator iterator1, int step);

  iterator begin() noexcept;

  iterator end() noexcept;

  iterator erase(iterator iterator1);

  bool isEmpty() const;

  void pushBack(const Contact contact);

  friend std::istream& operator>>(std::istream& in, Contact& contact);

  friend std::ostream& operator<<(std::ostream& out, Contact& contact);

private:
  std::list<Contact> contactsList_;

};

#endif //KOVALEVA_ANNA_B2_PHONEBOOK_HPP
