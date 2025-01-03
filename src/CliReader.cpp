#include "CliReader.h"

CliReader::CliReader(int argc, char* argv[]) : numberOfArgs(argc), args(argv, argv + argc), taskManager() {}

void CliReader::executeCommand() {
  if (this->numberOfArgs == 1) {
    this->taskManager.help();
  } else if (this->args.at(1).compare("list") == 0) {
    if (this->numberOfArgs == 2) {
      this->taskManager.listTasks();
    } else if (this->args.at(2).compare("clear") == 0) {
      this-> taskManager.clearList();
    }
  } else if (this->args.at(1).compare("help") == 0) {
    this->taskManager.help();
  } else if (this->args.at(1).compare("add") == 0) {
    this->taskManager.addTask(this->args.at(2));
  } else if (this->args.at(1).compare("remove") == 0) {
    try {
      int taskId = std::stoi(this->args.at(2));
      this->taskManager.removeTask(taskId);
    } catch (const std::invalid_argument& e) {
      std::cout << "Looks like you entered invalid task number. Try again." << std::endl;
    } catch (const std::out_of_range& e) {
      std::cout << "Looks like you've entered invalid task number. Try again." << std::endl;
    }
  } else {
    std::cout << "Looks like you've entered invalid command. Try again." << std::endl;
    this->taskManager.help();
  }
}

CliReader::~CliReader() {}