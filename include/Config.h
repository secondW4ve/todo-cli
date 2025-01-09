#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <regex>
#include "ConfigData.h"
#include "CustomException.h"

class Config {
  private:
    std::string pathToConfig;
    const std::string todoConfigFolderName = "todo-cli";
    const std::string todoConfigFileName = "todo.cfg";

  public:
    Config();
    ConfigData getConfigData();
};

#endif