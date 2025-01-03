#ifndef SQLITESTORAGE_H
#define SQLITESTORAGE_H

#include <iostream>
#include <vector>
#include <fstream>
#include <sqlite3.h>
#include "Config.h"
#include "Storage.h"

class SQLiteStorage : public Storage {
  protected:
    std::string pathToStorage;
    void executeSQL(sqlite3* db, const char* sql);
    sqlite3* openDbConnection() const;

  public:
    SQLiteStorage();
    std::vector<std::string> readList() const override;
    int getListSize() const override;
    void addToList(std::string task) override;
    void removeFromList(int index) override;
    void clearList() override;

    ~SQLiteStorage();

};

#endif