#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include "Storage.h"
#include "CustomException.h"

class TaskManager {
  private:
    Storage storage;

  public:
    TaskManager();

    void listTasks() const;
    void addTask(std::string task);
    void removeTask(int taskId);
    void help() const;
    void clearList();

    ~TaskManager();
};

#endif