#include "webview.h"

#include "server.cpp"
#include "loader.cpp"
#include <string>


#ifdef _WIN32
int WINAPI WinMain(HINSTANCE /*hInst*/, HINSTANCE /*hPrevInst*/,
                   LPSTR /*lpCmdLine*/, int /*nCmdShow*/) {
#else
int main() {
#endif  
  std::thread st = server::Init();
  webview::webview w(true, nullptr);

  w.set_title("Bind Example");
  w.set_size(480, 320, WEBVIEW_HINT_NONE);
  w.navigate("http://localhost:" + std::to_string(server::port));
  w.run();  

  return 0;
}
