#include "webview.h"
#include "server.cpp"

#include <iostream>


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif  
  std::thread thread = server::Init();
  webview::webview window(true, nullptr);

  window.set_title("Bind Example");
  window.set_size(480, 320, WEBVIEW_HINT_NONE);
  window.navigate(server::address);
  window.run();  

  return 0;
}
