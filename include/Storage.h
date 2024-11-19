#ifndef STORAGE_H
#define STORAGE_H

#include <iostream>
#include "Config.h"

class Storage {
  protected:
    std::string pathToStorage;

  public:
    virtual std::vector<std::string> readList() const = 0;
    virtual int getListSize() const = 0;
    virtual void addToList(std::string task) = 0;
    virtual void removeFromList(int index) = 0;
    virtual void clearList() = 0;

    virtual ~Storage() = default;

};

#endif