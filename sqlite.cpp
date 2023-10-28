#pragma once

#include <string>
#include <sqlite3.h>
#include <json.hpp>

int _sqlite3_exec_callback(void * data, int argc, char **row, char **column) {
  json::JSON c;
  for (int i = 0; i < argc; i++) c[column[i]] = row[i];
  ((json::JSON*)data)->append(c);
  return 0;
}

class SQLite {
  public:
    SQLite(const std::string filename) {
      sqlite3_open(filename.c_str(), &db);
    }

    json::JSON exec(const std::string query) {
      auto r = json::JSON::Load("[]");
      sqlite3_exec(db, query.c_str(), &_sqlite3_exec_callback, &r, nullptr);
      return r;
    }

    void close() {
      sqlite3_close(db);
    }

  protected:
    sqlite3 * db;

};
