#ifndef KOVALEVA_ANNA_B3_COMMANDS_HPP
#define KOVALEVA_ANNA_B3_COMMANDS_HPP

#include <string>
#include <functional>
#include <iosfwd>
#include "bookmark.hpp"

using function = std::function<void(Bookmark& phoneBook, std::ostream& out)>;

std::string parseBookmarkName(std::istream& in);

function add(std::istream& in);

function store(std::istream& in);

function insert(std::istream& in);

function deleteBookmark(std::istream& in);

function show(std::istream& in);

function move(std::istream& in);

void printInvalidCommand(Bookmark&, std::ostream& out);

std::istream& operator>>(std::istream& in, function& function);

#endif //KOVALEVA_ANNA_B3_COMMANDS_HPP
