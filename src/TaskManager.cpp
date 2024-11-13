#include "TaskManager.h"

TaskManager::TaskManager() : storage() {
  // create object of Storage
}

void TaskManager::listTasks() const {
  try {
    std::vector<std::string> tasks = this->storage.readList();
    if (tasks.size() == 0) {
      std::cout << "\tYour list is empty, use 'add <task name>' command to add a task" << std::endl;
      return;
    }
    for (int i = 0; i < tasks.size(); i++) {
      std::cout << i + 1 << ". " << tasks.at(i) << std::endl;
    }

    std::cout << std::endl;
  } catch (const CustomException& e) {
    std::cerr << "Something went wrong :( " << std::endl << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Something went really wrong :( " << std::endl << e.what() << std::endl;
  }
}

void TaskManager::addTask(std::string task) {
  try {
    this->storage.addToList(task);
  } catch (const CustomException& e) {
    std::cerr << "Something went wrong :( " << std::endl << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Something went really wrong :( " << std::endl << e.what() << std::endl;
  }
}

void TaskManager::removeTask(int taskId) {
  try {
    int taskListSize = this->storage.getListSize();

    if (taskId <= 0 || taskId > taskListSize) {
      std::cout << "*Task is invalid, please enter correct task id*" << std::endl;
      this->listTasks();
      return;
    }

    this->storage.removeFromList(taskId - 1);
  } catch (const CustomException& e) {
    std::cerr << "Something went wrong :( " << std::endl << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Something went really wrong :( " << std::endl << e.what() << std::endl;
  }
}

void TaskManager::help() const {
  std::cout << "Here are available commands that you can use:" << std::endl;
  std::cout << "\tlist - list your tasks" << std::endl;
  std::cout << "\tadd <task name> - add task to your list" << std::endl;
  std::cout << "\tremove <task id> - remove task with specific id from your list" << std::endl;
  std::cout << "\thelp - print available commands" << std::endl;
}

void TaskManager::clearList() {
  try {
    this->storage.clearList();
    std::cout << "Your task list was cleared and now it is empty" << std::endl;
  } catch (const CustomException& e) {
    std::cout << "Something went wrong :( " << std::endl << e.what() << std::endl;
  } catch (const std::exception& e) {
    std::cerr << "Something went really wrong :( " << std::endl << e.what() << std::endl;
  }
}

TaskManager::~TaskManager() {}