#include <string>
#include <json.hpp>
#include <asar.hpp>
#include <webview.h>

#include "sqlite.cpp"
#include "server.cpp"

webview::webview load(struct Asar::asar * resources, int * PORT) {
  json::JSON config = json::JSON::Load(Asar::content(resources, "resources.asar", {"delfos.config.json"})); 
  
  int width = config["window"]["width"].ToInt();
  int height = config["window"]["height"].ToInt();
  bool devTools = config["window"]["devTools"].ToBool();
  std::string title = config["window"]["title"].ToString();

  *PORT = config["server"]["port"].ToInt();

  webview::webview window(devTools, nullptr);
  window.set_title(title);
  window.set_size(width, height, WEBVIEW_HINT_NONE);
  window.navigate("http://localhost:" + std::to_string(*PORT));
 
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
  webview::webview window = load(&resources, PORT);
  std::thread server = server::Init(&resources, &db, *PORT);

  delete PORT;
  window.run();
  db.close();

  return 0;
}

