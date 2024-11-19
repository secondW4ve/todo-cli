#include "Storage.h"
#include "CustomException.h"

Storage::Storage() {
  Config conf;
  try {
    ConfigData confData = conf.getConfigData();
    this->storageType = confData.storageType;
    this->pathToStorage = confData.pathToTodoFile;
  } catch (const CustomException& e) {
    std::cerr << "Retrieving config failed: Error message:" << std::endl << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Something went really wrong :( " << std::endl << e.what() << std::endl;
  }
};

std::vector<std::string> Storage::readList() const {
  std::ifstream todoFile(this->pathToStorage);

  if (!todoFile) {
    throw CustomException("Error opening .todo file!");
  }

  std::vector<std::string> tasks;
  std::string line;
  while (std::getline(todoFile, line)) {
    tasks.push_back(line);
  }
  todoFile.close();

  return tasks;
}

int Storage::getListSize() const {
  return this->readList().size();
}

void Storage::addToList(std::string task) {
  std::ofstream todoFile(this->pathToStorage, std::ios::app);

  if (!todoFile) {
    throw CustomException("Error opening .todo file!");
  }

  todoFile << task << std::endl;
  todoFile.close();
}

void Storage::removeFromList(int index) {
  std::vector<std::string> tasks = this->readList();
  tasks.erase(tasks.begin() + index);
  
  std::ofstream todoFile(this->pathToStorage);

  if (!todoFile) {
    throw CustomException("Error opening .todo file!");
  }

  for (const auto& outputLine : tasks) {
    todoFile << outputLine << std::endl;
  }

  todoFile.close();
}

void Storage::clearList() {
  std::ofstream todoFile(this->pathToStorage, std::ios::trunc);

  if (!todoFile.is_open()) {
    throw CustomException("Error opening .todo file!");
  }

  todoFile.close();
}

Storage::~Storage() {}