#ifndef CONFIG_H
#define CONFIG_H

#include <iostream>
#include <filesystem>
#include <fstream>
#include <cstdlib>
#include "ConfigData.h"
#include "CustomException.h"

class Config {
  private:
    std::string pathToConfig;
    const std::string todoConfigFolderName = "todo-conf";
    const std::string todoConfigFileName = ".todo-conf";

  public:
    ConfigData getConfigData();
};

#endif