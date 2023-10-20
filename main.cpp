#include "webview.h"
#include "server.cpp"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif  
  struct parser::Asar resources;
  parser::Asar(&resources, "./app.asar");

  std::thread thread = server::Init(&resources);
  webview::webview window(true, nullptr);
  
  window.set_title("Bind Example");
  window.set_size(480, 320, WEBVIEW_HINT_NONE);
  window.navigate(server::address);
  window.run();

  resources.stream.close();

  return 0;
}

