#include "Config.h"

Config::Config() {
  const char* xdgConfigHome = std::getenv("XDG_CONFIG_HOME");
  std::string pathToConfigFolder;
  // If global config folder path is not set use default 
  if (!xdgConfigHome) {
    pathToConfigFolder = "/etc";
  } else {
    pathToConfigFolder = std::string(xdgConfigHome);
  }

  std::string pathToTodoConfigFolder = pathToConfigFolder + "/" + this->todoConfigFolderName;
  // if config folder for todo app doesn't exist then installation process went wrong
  if (!std::filesystem::exists(pathToTodoConfigFolder) || !std::filesystem::is_directory(pathToTodoConfigFolder)) {
    throw CustomException("Failed to find config directory at path: " + pathToTodoConfigFolder);
  }

  std::string pathToConfig = pathToTodoConfigFolder + "/" + this->todoConfigFileName;
  if (!std::filesystem::exists(pathToConfig)) {
    throw CustomException("Failed to find config file at path: " + pathToConfig);
  }

  this->pathToConfig = pathToConfig;
}

ConfigData Config::getConfigData() {
  std::ifstream confFile(this->pathToConfig);

  if (!confFile) {
    throw CustomException("Config file can't be read from conf file!");
  }

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(confFile, line)) {
    lines.push_back(line);
  }
  confFile.close();

  std::string storageType;
  std::string storagePath;
  std::regex storageTypePattern(std::string("STORAGE_TYPE") + R"(=(.+))");
  std::regex storagePathPattern(std::string("STORAGE_PATH") + R"(=(.+))");

  for (const auto& item : lines) {
    std::smatch match;
    if (std::regex_match(item, match, storageTypePattern)) {
      storageType = match[1];
      continue;
    }

    if (std::regex_match(item, match, storagePathPattern)) {
      storagePath = match[1];
    }
  }

  if (storageType.empty() || storagePath.empty()) {
    throw CustomException("Storage Type or Storage Path is not present in config file! Path to conf file: " + this->pathToConfig);
  }

  ConfigData conf;
  conf.storageType = storageType;
  conf.pathToTodoFile = storagePath;

  return conf;
}