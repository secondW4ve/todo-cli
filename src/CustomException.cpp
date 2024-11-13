#include "CustomException.h"

CustomException::CustomException(const std::string& msg): message(msg) {}

const char* CustomException::what() const noexcept {
  return this->message.c_str();
}