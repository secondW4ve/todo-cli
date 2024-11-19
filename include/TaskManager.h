#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <iostream>
#include "Config.h"
#include "ConfigData.h"
#include "Storage.h"
#include "FileStorage.h"
#include "SQLiteStorage.h"
#include "CustomException.h"

class TaskManager {
  private:
    std::unique_ptr<Storage> storage;

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