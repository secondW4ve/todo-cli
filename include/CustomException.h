#ifndef STORAGEEXCEPTION_H
#define STORAGEEXCEPTION_H

#include <exception>
#include <iostream>

class CustomException : public std::exception {
  private:
    std::string message;

  public:
    explicit CustomException(const std::string& msg);
    const char* what() const noexcept override;
};

#endif