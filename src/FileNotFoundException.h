#ifndef FILENOTFOUNDEXCEPTION_H
#define FILENOTFOUNDEXCEPTION_H

#include <exception>

class FileNotFoundException : public std::exception
{
public:
  FileNotFoundException(const std:: string &file) : txt(file) {}

  const char *what() const throw();

private:
  const std::string &txt;
};

#endif // FILENOTFOUNDEXCEPTION_H
