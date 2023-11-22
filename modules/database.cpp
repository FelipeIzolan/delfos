#pragma once

#include "webview.h"
#include <sqlite3.h>
#include <json.hpp>
#include <string>

int _sqlite3_exec_callback(void * data, int argc, char **row, char **column) {
  json::JSON c;
  for (int i = 0; i < argc; i++) c[column[i]] = row[i];
  ((json::JSON*)data)->append(c);
  return 0;
}

class Database {
  public:
    Database(const std::string filename) {
      sqlite3_open(filename.c_str(), &db);
    }

    std::string exec(const std::string query) {
      auto r = json::JSON::Load("[]");
      sqlite3_exec(db, query.c_str(), &_sqlite3_exec_callback, &r, nullptr);
      return r.stringify();
    }

    void close() {
      sqlite3_close(db);
    }

  protected:
    sqlite3 * db;

};

void DatabaseWebviewLoader(webview::webview * webview, Database * database) {
  webview->bind("_db_query", [database](const std::string param) {
    std::string query = json::JSON::Load(param)[0].ToString();
    return database->exec(query);
  });
}
