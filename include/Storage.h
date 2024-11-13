#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include <vector>
#include <fstream>

class Storage {
  private:
    std::string pathToStorageFile = "/home/yurchyk/.todo";

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