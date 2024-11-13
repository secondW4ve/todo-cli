#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <iostream>

struct ConfigData {
  // 0 is file 1 is database
  int storageType;
  std::string pathToTodoFile;
  // Will need to add db connection details probably
};

#endif