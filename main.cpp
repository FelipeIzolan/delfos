#include <webview.h>
#include <json.hpp>
#include <asar.hpp>

#include "modules/sqlite.cpp"
#include "modules/storage.cpp"
#include "server.cpp"

void load(webview::webview * window, Asar * resources, SQLite * db, Storage * storage) {
  json::JSON config = json::JSON::Load(resources->content("/delfos.config.json")); 
 
  int width = config["window"]["width"].ToInt();
  int height = config["window"]["height"].ToInt();
  std::string title = config["window"]["title"].ToString();

  // int PORT = config["server"]["port"].ToInt();

  window->set_title(title);
  window->set_size(width, height, WEBVIEW_HINT_NONE);
  window->navigate("http://localhost:9999");

  window->bind("_db_query", [db](const std::string param) {
    std::string query = json::JSON::Load(param)[0].ToString();
    return db->exec(query);
  });

  window->bind("_storage_set", [storage](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    storage->set(p[0].ToString(), p[1].ToString());
    return "ok";
  });

  window->bind("_storage_get", [storage](std::string param) {
    std::string key = json::JSON::Load(param)[0].ToString();
    return storage->get(key);
  });

  window->bind("_storage_del", [storage](std::string param) {
    std::string key = json::JSON::Load(param)[0].ToString();
    storage->del(key);
    return "ok";   
  });
}

int main() {
  Asar resources("resources.asar");
  SQLite db("./data/.database.sql");
  Storage storage("./data/.storage.json");

  webview::webview window(true, nullptr);
  load(&window, &resources, &db, &storage);
  std::thread server = server::Init(&resources, 9999);

  window.run();

  db.close();
  storage.close();

  return 0;
}

