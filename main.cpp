#include <string>

#include "server.cpp"
#include "webview.h"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#endif
#ifndef _WIN32
int main() {
#endif  
  struct parser::Asar resources; 
  parser::Asar(&resources);

  // nlohmann::json config = parser::JSON(parser::AsarContent(&resources, "/delfos.config.json")); 
  std::thread thread = server::Init(&resources);
  // 
  // std::string title = config["window"]["title"];
  // int width = config["window"]["width"];
  // int height = config["window"]["height"];
  // bool devTools = config["window"]["devTools"];

  webview::webview window(true, nullptr);
  window.set_title("Felkip");
  window.set_size(1280, 720, WEBVIEW_HINT_NONE);
  window.navigate(server::address);
  window.run();

  // config.clear();


  return 0;
}

