#ifndef FILESTORAGE_H
#define FILESTORAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include "Config.h"
#include "Storage.h"
#include "CustomException.h"

class FileStorage : public Storage {
  protected:
    std::string pathToStorage;

  public:
    FileStorage();
    std::vector<std::string> readList() const override;
    int getListSize() const override;
    void addToList(std::string task) override;
    void removeFromList(int index) override;
    void clearList() override;

    ~FileStorage();

};

#endif