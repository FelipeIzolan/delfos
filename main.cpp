#include <string>

#include "webview.h"

#include "json.hpp"
#include "asar.hpp"

#include "server.cpp"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#endif
#ifndef _WIN32
int main() {
#endif  
  struct Asar::asar resources; 
  Asar::parser(&resources);

  json::JSON config = json::JSON::Load(Asar::content(&resources, {"delfos.config.json"})); 
  std::thread thread = server::Init(&resources);
  //
  std::string title = config["window"]["title"].ToString();
  int width = config["window"]["width"].ToInt();
  int height = config["window"]["height"].ToInt();
  bool devTools = config["window"]["devTools"].ToBool();

  webview::webview window(devTools, nullptr);
  window.set_title(title);
  window.set_size(width, height, WEBVIEW_HINT_NONE);
  window.navigate("http://localhost:9999");
  window.run();

  return 0;
}

