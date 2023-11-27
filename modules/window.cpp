#include <string>
#include "json.hpp"
#include "webview.h"

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _linux_
#endif

class Window {
  public:
    Window(void * ptr) {
      window = ptr;
    }

    void maximize() {
      #ifdef _WIN32
      SendMessage((HWND) window, WM_SYSCOMMAND, SC_MAXIMIZE, 0);
      #endif

      #ifdef _linux_
      #endif
    }
    
    void restore() {
      #ifdef _WIN32
      SendMessage((HWND) window, WM_SYSCOMMAND, SC_RESTORE, 0);
      #endif

      #ifdef _linux_
      #endif
    }

    void minimize() {
      #ifdef _WIN32
      SendMessage((HWND) window, WM_SYSCOMMAND, SC_MINIMIZE, 0);
      #endif

      #ifdef _linux_
      #endif
    }

    void setPosition(int x, int y) {
      #ifdef _WIN32
      SetWindowPos((HWND) window, HWND_TOP, x, y, 0, 0, SWP_NOSIZE);
      #endif
    
      #ifdef _linux_
      #endif
    }

    void setIcon(const std::string source) {
      #ifdef _WIN32
        HANDLE hIcon = LoadImage(GetModuleHandle(0), source.c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
        SendMessage((HWND) window, WM_SETICON, ICON_SMALL, (LPARAM) hIcon);
        SendMessage((HWND) window, WM_SETICON, ICON_BIG, (LPARAM) hIcon);
      #endif
 
      #ifdef _linux_
      #endif
    }


  protected:
    void * window;
};

void WindowWebviewLoader(webview::webview * webview, Window * window) {
  webview->bind("_window_set_title", [webview](const std::string param) {
    std::string p = json::JSON::Load(param)[0].ToString();
    webview->set_title(p);
    return "ok";
  });

  webview->bind("_window_set_position", [window](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    window->setPosition(p[0].ToInt(), p[1].ToInt());
    return "ok";
  });

  webview->bind("_window_set_size", [webview](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    webview->set_size(p[0].ToInt(), p[1].ToInt(), WEBVIEW_HINT_NONE);
    return "ok";
  });

  webview->bind("_window_maximize", [window](const std::string null) {
    window->maximize();
    return "ok";
  });
  
  webview->bind("_window_restore", [window](const std::string null) {
    window->restore();
    return "ok";
  });
  
  webview->bind("_window_minimize", [window](const std::string null) {
    window->minimize();
    return "ok";
  });

  webview->bind("_window_close", [webview](const std::string null) {
    webview->terminate();
    return "ok";
  });
}
