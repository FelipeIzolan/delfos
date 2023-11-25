#include <webview.h>
#include <json.hpp>
#include <asar.hpp>

#include "modules/database.cpp"
#include "modules/storage.cpp"
#include "modules/window.cpp"
#include "modules/system.cpp"

#include "server.cpp"

int load(webview::webview * webview, Asar * resources, Window * window) {
  json::JSON config = json::JSON::Load(resources->content("/delfos.config.json")); 
 
  int width = config["window"]["width"].ToInt();
  int height = config["window"]["height"].ToInt();
  int port = config["server"]["port"].ToInt();
  std::string title = config["window"]["title"].ToString();

  webview->set_title(title);
  webview->set_size(width, height, WEBVIEW_HINT_NONE);
  webview->navigate("http://localhost:" + std::to_string(port));
  window->setIcon("icon.ico");

  return port;
}

int main() {
  Asar resources("resources.asar");
  
  webview::webview webview(true, nullptr);

  Database database("./data/.database.sql");
  Storage storage("./data/.storage.json");
  Window window(webview.window()); 
  System system;

  DatabaseWebviewLoader(&webview, &database);
  StorageWebviewLoader(&webview, &storage);
  WindowWebviewLoader(&webview, &window);
  SystemWebviewLoader(&webview, &system);

  int port = load(&webview, &resources, &window);
  std::thread server = server::Init(&resources, port);

  webview.run();

  database.close();
  storage.close();

  return 0;
}

