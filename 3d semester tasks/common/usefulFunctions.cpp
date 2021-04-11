#include "usefulFunctions.hpp"

std::istream& skipWsExceptNewLine(std::istream& in)
{
  for (char ch = static_cast<char>(in.get());
       isspace(ch) && (ch != '\n') && (ch != std::char_traits<char>::eof()); ch = static_cast<char>(in.get()))
  { }
  if (!in.eof())
  {
    in.unget();
  }
  return in;
}
