#include "Config.h"

Config::Config() {
  const char* home = std::getenv("HOME");
  const char* xdgConfigHome = std::getenv("XDG_CONFIG_HOME");
  std::string pathToConfigFolder;
  // If global config folder path is not set use default 
  if (!xdgConfigHome) {
    if (home) {
      pathToConfigFolder = std::string(home) + "/.config";
    } else {
      std::cerr << "Neither XDG_CONFIG_HOME nor HOME is set." << std::endl;
    }
  } else {
    pathToConfigFolder = std::string(xdgConfigHome);
  }

  std::string pathToTodoConfigFolder = pathToConfigFolder + "/" + this->todoConfigFolderName;
  // if config folder for todo app doesn't exist then create it
  if (!std::filesystem::exists(pathToTodoConfigFolder) || !std::filesystem::is_directory(pathToTodoConfigFolder)) {
    std::filesystem::path path = pathToConfigFolder + "/" + this->todoConfigFolderName;
    if (!std::filesystem::create_directory(path)) {
      std::cerr << "Failed to create config directory at path: " << path << std::endl;
      return;
    }
  }
  
  // if todo conf file doesn't exist it will create it
  this->pathToConfig = pathToConfigFolder + "/" + this->todoConfigFileName;
  std::ofstream todoConf(this->pathToConfig);
  todoConf.close();
}

ConfigData Config::getConfigData() {
  std::ifstream confFile(this->pathToConfig);

  if (!confFile) {
    throw CustomException("Config file can't be read from conf file!");
  }

  std::vector<std::string> lines;
}