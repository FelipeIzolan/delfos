#include <exception>
#include <string>

#include <webview.h>
#include <json.hpp>
#include <asar.hpp>

#include "modules/sqlite.cpp"
#include "modules/storage.cpp"
#include "server.cpp"

webview::webview load(struct Asar::asar * resources, SQLite * db, Storage * storage, int * PORT) {
  
  // --- CONFIG
  json::JSON config = json::JSON::Load(Asar::content(resources, "resources.asar", {"delfos.config.json"})); 
  
  int width = config["window"]["width"].ToInt();
  int height = config["window"]["height"].ToInt();
  bool devTools = config["window"]["devTools"].ToBool();
  std::string title = config["window"]["title"].ToString();
  // ---

  *PORT = config["server"]["port"].ToInt();
  
  // --- WINDOW
  webview::webview window(devTools, nullptr);
  window.set_title(title);
  window.set_size(width, height, WEBVIEW_HINT_NONE);
  window.navigate("http://localhost:" + std::to_string(*PORT));
  // ---

  // --- BIND
  window.bind("_db_query", [db](const std::string param) {
    std::string query = json::JSON::Load(param)[0].ToString();
    return db->exec(query);
  });

  window.bind("_storage_set", [storage](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    storage->set(p[0].ToString(), p[1].ToString());
    return "ok";
  });

  window.bind("_storage_get", [storage](std::string param) {
    std::string key = json::JSON::Load(param)[0].ToString();
    return storage->get(key);
  });

  window.bind("_storage_del", [storage](std::string param) {
    std::string key = json::JSON::Load(param)[0].ToString();
    storage->del(key);
    return "ok";   
  });
  // ---

  return window;
}

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#endif
#ifndef _WIN32
int main() {
#endif
  int * PORT = new int;

  struct Asar::asar resources; 
  Asar::parser(&resources, "resources.asar");

  SQLite db(".database.sql");
  Storage storage;

  webview::webview window = load(&resources, &db, &storage, PORT);
  std::thread server = server::Init(&resources, *PORT);

  delete PORT;
  window.run();
 
  db.close();
  storage.close();

  return 0;
}

