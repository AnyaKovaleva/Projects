#include <iostream>
#include <functional>
#include <map>
#include <string>
#include <stdexcept>

#include "queueWithPriority.hpp"

using priority = QueueWithPriority<std::string>::ElementPriority;

static std::function<void(QueueWithPriority<std::string>&, std::ostream&)> convertCommand(std::istream&);

void printInvalidCommand(QueueWithPriority<std::string>&, std::ostream& out);

static std::function<void(QueueWithPriority<std::string>&, std::ostream&)> addCommand(std::istream&);

static std::function<void(QueueWithPriority<std::string>&, std::ostream&)> getCommand(std::istream&);

static std::function<void(QueueWithPriority<std::string>&, std::ostream&)> accelerateCommand(std::istream&);

std::istream& skipwsExceptNewLine(std::istream&);

void taskOne(std::istream& in, std::ostream& out)
{
  QueueWithPriority<std::string> queue;
  while (in >> std::ws && !in.eof())
  {
    convertCommand(in)(queue, out);
  }
  if (!in.eof())
  {
    throw std::invalid_argument("Error while reading");
  }
}

std::function<void(QueueWithPriority<std::string>&, std::ostream&)> convertCommand(std::istream& in)
{
  static const std::map<std::string, std::function<void(QueueWithPriority<std::string>&, std::ostream&)> (*)(
    std::istream&)> commands
    {
      {"add",        addCommand},
      {"get",        getCommand},
      {"accelerate", accelerateCommand}
    };

  std::string command;
  in >> std::ws >> command;
  auto iter = commands.find(command);
  if (iter != commands.end())
  {
    return iter->second(in);
  }
  else
  {
    return printInvalidCommand;
  }

}

void printInvalidCommand(QueueWithPriority<std::string>&, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

std::function<void(QueueWithPriority<std::string>&, std::ostream&)> addCommand(std::istream& in)
{
  std::string strPriority;
  in >> skipwsExceptNewLine >> strPriority;

  if (strPriority.empty() || in.fail())
  {
    return printInvalidCommand;
  }

  std::string data;
  std::getline(in >> skipwsExceptNewLine, data);

  if (data.empty())
  {
    return printInvalidCommand;
  }

  priority priorityVal = priority::LOW;

  static const std::map<std::string, priority> priorities
    {
      {"low",    priority::LOW},
      {"normal", priority::NORMAL},
      {"high",   priority::HIGH}
    };
  auto iter = priorities.find(strPriority);
  if (iter != priorities.end())
  {
    priorityVal = iter->second;
  }
  else
  {
    return printInvalidCommand;
  }
  return [data, priorityVal](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    queue.add(data, priorityVal);
  };
}

std::function<void(QueueWithPriority<std::string>&, std::ostream&)> getCommand(std::istream&)
{
  return [](QueueWithPriority<std::string>& queue, std::ostream& out)
  {
    if (queue.handle([&out](const std::string& str)
                     {
                       out << str << "\n";
                       return 0;
                     }) == 1)
    {
      out << "<EMPTY>\n";
    }
  };
}

std::function<void(QueueWithPriority<std::string>&, std::ostream&)> accelerateCommand(std::istream&)
{
  return [](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    queue.accelerate();
  };
}

std::istream& skipwsExceptNewLine(std::istream& in)
{
  for (char ch = static_cast<char>(in.get()); isspace(ch) && (ch != '\n'); ch = static_cast<char>(in.get()))
  { }
  in.unget();
  return in;
}

