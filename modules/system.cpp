#include <iostream>
#include <webview.h>
#include <json.hpp>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef linux
#include <signal.h>
#include <sys/types.h>
#endif

class System {
  public:

    void kill(int pid) {
      
      // Don't forget to test ::kill from signal.h on windows!
      #ifdef _WIN32
      std::string command = "taskkill /F /PID " + std::to_string(pid);
      WinExec(command.c_str(), SW_HIDE);
      #endif
 
      #ifdef linux
      if (::kill(pid, SIGKILL) == 0) std::cout << "killed\n";
      else std::cout << "not killed \n";
      #endif
    }

    void exec() {}

};

void system_webview_loader(webview::webview * webview, System * system) {
  webview->bind("_system_kill", [system](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    system->kill(p[0].ToInt());
    return "ok";
  });
}
