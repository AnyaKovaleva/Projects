#include <iostream>
#include <iterator>
#include <stdexcept>
#include <set>

void taskOne(std::istream& in, std::ostream& out)
{
  std::set<std::string> uniqueWords{std::istream_iterator<std::string>(in),
                                    std::istream_iterator<std::string>()};
  if (!in.eof())
  {
    throw std::ios_base::failure("Reading failed");
  }

  std::copy(uniqueWords.begin(), uniqueWords.end(), std::ostream_iterator<std::string>(out, "\n"));
}
