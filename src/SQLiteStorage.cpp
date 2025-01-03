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

  sqlite3* db = this->openDbConnection();

  const char* createTableSQL = R"(
    CREATE TABLE IF NOT EXISTS tasks (
      id INTEGER PRIMARY KEY AUTOINCREMENT,
      description TEXT NOT NULL,
      completed BOOL NOT NULL DEFAULT false
    );
  )";
  this->executeSQL(db, createTableSQL);

  sqlite3_close(db);
}

void SQLiteStorage::executeSQL(sqlite3* db, const char* sql) {
  char* errMsg = nullptr;
  int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errMsg);
  if (rc != SQLITE_OK) {
    sqlite3_free(errMsg);
    throw CustomException("SQL execution failed: " + std::string(errMsg));
  }
}

sqlite3* SQLiteStorage::openDbConnection() const {
  sqlite3* db;
  int rc = sqlite3_open(this->pathToStorage.c_str(), &db);
  if (rc) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw CustomException("Can't open database in specified location: " + this->pathToStorage + "\tError message: " + errMsg);
  }

  return db;
}

std::vector<std::string> SQLiteStorage::readList() const {
  std::vector<std::string> tasks;
  sqlite3* db = this->openDbConnection();

  const char* queryTasks = R"(
    SELECT * from tasks;
  )";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(db, queryTasks, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw CustomException("Failed to prepare statement: " + errMsg);
  }

  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::string description = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
    bool completed = sqlite3_column_int(stmt, 2) != 0;

    tasks.push_back(description);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return tasks;
}

int SQLiteStorage::getListSize() const {
  sqlite3* db = this->openDbConnection();

  const char* countTasks = R"(
    SELECT COUNT(*) from tasks;
  )";
  sqlite3_stmt* stmt;
  int rc = sqlite3_prepare_v2(db, countTasks, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw CustomException("Failed to prepare statement: " + errMsg);
  }

  int taskCount = 0;
  if (sqlite3_step(stmt) == SQLITE_ROW) {
    taskCount = sqlite3_column_int(stmt, 0);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
  return taskCount;
}

void SQLiteStorage::addToList(std::string task) {
  sqlite3* db = this->openDbConnection();

  const char* insertTask = R"(
    INSERT INTO tasks (description) VALUES (?);
  )";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(db, insertTask, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw CustomException("Failed to prepare statement: " + errMsg);
  }

  sqlite3_bind_text(stmt, 1, task.c_str(), -1, SQLITE_STATIC);

  if (sqlite3_step(stmt) != SQLITE_DONE) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    throw CustomException("Failed to insert task to db: " + errMsg);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void SQLiteStorage::removeFromList(int index) {
  std::vector<std::string> tasks = this->readList();
  std::string description = tasks.at(index);

  sqlite3* db = this->openDbConnection();
  const char* deleteTask = R"(
    DELETE FROM tasks WHERE description LIKE ?;
  )";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(db, deleteTask, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::string errorMsg = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw CustomException("Failed to prepare delete query: " + errorMsg);
  }

  sqlite3_bind_text(stmt, 1, description.c_str(), -1, SQLITE_STATIC);
  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    throw CustomException("Failed to execute delete query: " + errMsg);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

void SQLiteStorage::clearList() {
  sqlite3* db = this->openDbConnection();
  const char* deleteTask = R"(
    DELETE FROM tasks;
  )";
  sqlite3_stmt* stmt;

  int rc = sqlite3_prepare_v2(db, deleteTask, -1, &stmt, nullptr);
  if (rc != SQLITE_OK) {
    std::string errorMsg = sqlite3_errmsg(db);
    sqlite3_close(db);
    throw CustomException("Failed to prepare delete query: " + errorMsg);
  }

  rc = sqlite3_step(stmt);
  if (rc != SQLITE_DONE) {
    std::string errMsg = sqlite3_errmsg(db);
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    throw CustomException("Failed to execute delete query: " + errMsg);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);
}

SQLiteStorage::~SQLiteStorage() {}