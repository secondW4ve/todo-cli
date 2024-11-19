#include "SQLiteStorage.h"

SQLiteStorage::SQLiteStorage() {
  Config conf;
  try {
    ConfigData confData = conf.getConfigData();
    this->pathToStorage = confData.pathToTodoFile;
  } catch (const CustomException& e) {
    std::cerr << "Retrieving config failed: Error message:" << std::endl << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Something went really wrong :( " << std::endl << e.what() << std::endl;
  }
}

std::vector<std::string> SQLiteStorage::readList() const {
  // Do implementation
  std::vector<std::string> empty;
  return empty;
}

int SQLiteStorage::getListSize() const {
  // Do implementation

  return 0;
}

void SQLiteStorage::addToList(std::string task) {
  // Do implementation
}

void SQLiteStorage::removeFromList(int index) {
  // Do implementation
}

void SQLiteStorage::clearList() {
  // Do implementation
}

SQLiteStorage::~SQLiteStorage() {}