#include <iostream>
#include <string>
#include <algorithm>
#include "bookmark.hpp"

Bookmark::Bookmark()
{
  bookmarks_["current"] = phoneBook_.begin();
}

void Bookmark::add(const PhoneBook::Contact& contact)
{
  phoneBook_.pushBack(contact);

  if (phoneBook_.begin() == --phoneBook_.end())
  {
    std::for_each(bookmarks_.begin(), bookmarks_.end(), [&](auto& it)
    {
      it.second = phoneBook_.begin();
    });
  }
}

void Bookmark::store(const std::string& markName, const std::string& newMarkName, std::ostream& out)
{
  auto it = bookmarks_.find(markName);
  if (it != bookmarks_.end())
  {
    bookmarks_.emplace(newMarkName, it->second);
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void Bookmark::insertAfter(const std::string& markName, const PhoneBook::Contact& contact, std::ostream& out)
{
  auto it = bookmarks_.find(markName);
  if (it != bookmarks_.end())
  {
    if (phoneBook_.isEmpty())
    {
      add(contact);
    }
    else
    {
      phoneBook_.insertAfter(it->second, contact);
    }
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void Bookmark::insertBefore(const std::string& markName, const PhoneBook::Contact& contact, std::ostream& out)
{
  auto it = bookmarks_.find(markName);
  if (it != bookmarks_.end())
  {
    if (phoneBook_.isEmpty())
    {
      add(contact);
    }
    else
    {
      phoneBook_.insertBefore(it->second, contact);
    }
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void Bookmark::deleteBookmark(const std::string& markName, std::ostream& out)
{
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  else
  {
    auto deleteIt = it->second;
    auto bookmark = bookmarks_.begin();
    while (bookmark != bookmarks_.end())
    {
      if (bookmark->second == deleteIt)
      {
        if (std::next(bookmark->second) == phoneBook_.end())
        {
          bookmark->second = std::prev(deleteIt);
        }
        else
        {
          bookmark->second = std::next(deleteIt);
        }
      }
      bookmark++;
    }
    phoneBook_.erase(deleteIt);
  }
}

void Bookmark::showBookmark(const std::string& markName, std::ostream& out) const
{
  auto it = bookmarks_.find(markName);
  if (it != bookmarks_.end())
  {
    if (phoneBook_.isEmpty())
    {
      out << "<EMPTY>\n";
      return;
    }
    out << *it->second;
    return;
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void Bookmark::moveBookmark(const std::string& markName, positionToMove position, std::ostream& out)
{
  auto it = bookmarks_.find(markName);
  if (it == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  if (position == positionToMove::FIRST)
  {
    it->second = phoneBook_.begin();
  }
  if (position == positionToMove::LAST)
  {
    it->second = --phoneBook_.end();
  }

}

void Bookmark::moveBookmark(const std::string& markName, int steps, std::ostream& out)
{
  auto it = bookmarks_.find(markName);
  if (it != bookmarks_.end())
  {
    it->second = phoneBook_.move(it->second, steps);
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

