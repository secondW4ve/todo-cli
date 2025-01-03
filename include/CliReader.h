#ifndef CLIREADER_H
#define CLIREADER_H

#include <iostream>
#include <vector>
#include "TaskManager.h"

class CliReader {
  private:
    int numberOfArgs;
    std::vector<std::string> args;
    TaskManager taskManager;

  public:
    CliReader(int argc, char* argv[]);

    void executeCommand();

    ~CliReader();
};

#endif