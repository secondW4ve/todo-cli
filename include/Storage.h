#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Config.h"

class Storage {
  private:
    std::string pathToStorage;
    std::string storageType;

  public:
    Storage();

    std::vector<std::string> readList() const;
    int getListSize() const;
    void addToList(std::string task);
    void removeFromList(int index);
    void clearList();

    ~Storage();

};

#endif