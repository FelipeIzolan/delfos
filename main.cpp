#include <webview.h>
#include <json.hpp>
#include <asar.hpp>

#include "modules/database.cpp"
#include "modules/storage.cpp"
#include "modules/window.cpp"
#include "modules/system.cpp"

#include "server.cpp"

int main() {   
  Asar resources("resources.asar");
  json::JSON config = json::JSON::Load(resources.content("/delfos.config.json"));  

  webview::webview webview(config["dev_tools"].ToBool(), nullptr);

  Database database("./data/.database.sql");
  Storage storage("./data/.storage.json");
  Window window(webview.window()); 
  System system;

  DatabaseWebviewLoader(&webview, &database);
  StorageWebviewLoader(&webview, &storage);
  WindowWebviewLoader(&webview, &window);
  SystemWebviewLoader(&webview, &system);
  
  webview.set_title(config["window"]["title"].ToString());
  webview.set_size(config["window"]["width"].ToInt(), config["window"]["height"].ToInt(), WEBVIEW_HINT_NONE);
  window.set_icon("icon.ico");

  if (!config["window"]["min_width"].IsNull() && !config["window"]["min_height"].IsNull())
    webview.set_size(config["window"]["min_width"].ToInt(), config["window"]["min_height"].ToInt(), WEBVIEW_HINT_MIN);

  if (!config["window"]["max_width"].IsNull() && !config["window"]["max_height"].IsNull())
    webview.set_size(config["window"]["max_width"].ToInt(), config["window"]["max_height"].ToInt(), WEBVIEW_HINT_MAX);

  std::thread thread(server::Server, &resources, &webview);
  webview.run();

  database.close();
  storage.close();

  server::quit = true;
  thread.join();

  return 0;
}

