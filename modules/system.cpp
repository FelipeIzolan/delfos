#include <webview.h>
#include <json.hpp>
#include <stdlib.h>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

class System {
  public:

    void kill(int pid) {
      #ifdef _WIN32
      std::string command = "taskkill /F /PID " + std::to_string(pid);
      WinExec(command.c_str(), SW_HIDE);
      #endif

      // need a test!
      #ifdef _linux_
      std::string command = "kill " + std::to_string(pid);
      system(command.c_str());
      #endif
    }

    void exec() {}

};

void SystemWebviewLoader(webview::webview * webview, System * system) {
  webview->bind("_system_kill", [system](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    system->kill(p[0].ToInt());
    return "ok";
  });
}
