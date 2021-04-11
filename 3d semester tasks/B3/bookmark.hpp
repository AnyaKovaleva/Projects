#ifndef KOVALEVA_ANNA_B3_BOOKMARK_HPP
#define KOVALEVA_ANNA_B3_BOOKMARK_HPP

#include <map>
#include <iostream>
#include <string>
#include "phoneBook.hpp"

class Bookmark
{
public:
  enum positionToMove
  {
    FIRST,
    LAST
  };

  Bookmark();

  void add(const PhoneBook::Contact& contact);

  void store(const std::string& markName, const std::string& newMarkName, std::ostream& out);

  void insertAfter(const std::string& markName, const PhoneBook::Contact& contact, std::ostream& out);

  void insertBefore(const std::string& markName, const PhoneBook::Contact& contact, std::ostream& out);

  void deleteBookmark(const std::string& markName, std::ostream& out);

  void showBookmark(const std::string& markName, std::ostream& out) const;

  void moveBookmark(const std::string& markName, positionToMove position, std::ostream& out);

  void moveBookmark(const std::string& markName, int steps, std::ostream& out);

private:
  PhoneBook phoneBook_;
  std::map<std::string, PhoneBook::iterator> bookmarks_;
};

#endif //KOVALEVA_ANNA_B3_BOOKMARK_HPP
