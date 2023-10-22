#include <string>

#include "webview.h"

#include "server.cpp"
#include "parser.cpp"
#include "json.hpp"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#endif
#ifndef _WIN32
int main() {
#endif  
  struct parser::Asar resources; 
  parser::Asar(&resources);

  json::JSON config = parser::JSON(parser::AsarContent(&resources, "/delfos.config.json")); 
  std::thread thread = server::Init(&resources);
  
  std::string title = config["window"]["title"].ToString();
  int width = config["window"]["width"].ToInt();
  int height = config["window"]["height"].ToInt();
  bool devTools = config["window"]["devTools"].ToBool();

  webview::webview window(devTools, nullptr);
  window.set_title(title);
  window.set_size(width, height, WEBVIEW_HINT_NONE);
  window.navigate(server::address);
  window.run();

  return 0;
}

