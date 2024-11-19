#ifndef CONFIGDATA_H
#define CONFIGDATA_H

#include <iostream>

struct ConfigData {
  // FILE is file SQLITE is database
  std::string storageType;
  std::string pathToTodoFile;
  // Will need to add db connection details probably
};

#endif