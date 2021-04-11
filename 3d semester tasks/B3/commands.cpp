#include "commands.hpp"

#include <cctype>
#include <limits>
#include <stdexcept>
#include <iostream>
#include "usefulFunctions.hpp"

std::string parseBookmarkName(std::istream& in)
{
  std::string bookmark;
  in >> skipWsExceptNewLine >> bookmark;

  if (bookmark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  for (auto ch: bookmark)
  {
    if (!std::isalnum(ch) && ch != '-')
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return bookmark;
}

function add(std::istream& in)
{
  PhoneBook::Contact newContact;
  in >> newContact;

  if (in.fail())
  {
    in.clear();
    return printInvalidCommand;
  }

  return [newContact](Bookmark& bookmark, std::ostream&)
  {
    bookmark.add(newContact);
  };
}

function store(std::istream& in)
{
  std::string markName;
  std::string newMarkName;
  try
  {
    markName = parseBookmarkName(in);
    newMarkName = parseBookmarkName(in);
  }
  catch (const std::invalid_argument&)
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return printInvalidCommand;
  }

  return [markName, newMarkName](Bookmark& bookmark, std::ostream& out)
  {
    bookmark.store(markName, newMarkName, out);
  };
}

function insert(std::istream& in)
{
  std::string moveStep;
  in >> skipWsExceptNewLine >> moveStep;

  std::string markName;
  try
  {
    markName = parseBookmarkName(in);
  }
  catch (const std::invalid_argument&)
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return printInvalidCommand;
  }

  PhoneBook::Contact newContact;
  in >> newContact;
  if (in.fail())
  {
    in.clear();
    return printInvalidCommand;
  }

  return [moveStep, markName, newContact](Bookmark& bookmark, std::ostream& out)
  {
    if (moveStep == "before")
    {
      bookmark.insertBefore(markName, newContact, out);
    }
    else if (moveStep == "after")
    {
      bookmark.insertAfter(markName, newContact, out);
    }
    else
    {
      printInvalidCommand(bookmark, out);
    }
  };

}

function deleteBookmark(std::istream& in)
{
  std::string bookmarkName = parseBookmarkName(in);
  return [bookmarkName](Bookmark& bookmark, std::ostream& out)
  {
    bookmark.deleteBookmark(bookmarkName, out);
  };
}

function show(std::istream& in)
{
  std::string bookmarkName = parseBookmarkName(in);
  return [bookmarkName](Bookmark& bookmark, std::ostream& out)
  {
    bookmark.showBookmark(bookmarkName, out);
  };
}

function move(std::istream& in)
{
  std::string markName = parseBookmarkName(in);
  std::string step;
  in >> skipWsExceptNewLine >> step;
  return [markName, step](Bookmark& bookmark, std::ostream& out)
  {
    if (step == "first")
    {
      Bookmark::positionToMove pos = Bookmark::positionToMove::FIRST;
      bookmark.moveBookmark(markName, pos, out);
      return;
    }

    if (step == "last")
    {
      Bookmark::positionToMove pos = Bookmark::positionToMove::LAST;
      bookmark.moveBookmark(markName, pos, out);
      return;
    }

    int count = 0;
    try
    {
      count = std::stoi(step);
    }
    catch (const std::invalid_argument&)
    {
      out << "<INVALID STEP>\n";
      return;
    }
    bookmark.moveBookmark(markName, count, out);
  };
}

void printInvalidCommand(Bookmark&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

std::istream& operator>>(std::istream& in, function& function)
{
  static const std::map<std::string, std::function<std::function<void(Bookmark& phoneBook,
                                                                      std::ostream& out)>(std::istream&)>> table =
    {
      {"add",    add},
      {"store",  store},
      {"insert", insert},
      {"delete", deleteBookmark},
      {"show",   show},
      {"move",   move}
    };

  std::string command;
  in >> std::ws >> command;
  if (command.empty())
  {
    return in;
  }

  auto it = table.find(command);

  if (it == table.end())
  {
    function = printInvalidCommand;
    return in;
  }
  try
  {
    function = (*it).second(in);
  }
  catch (const std::invalid_argument&)
  {
    in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    function = printInvalidCommand;
  }
  return in;
}

