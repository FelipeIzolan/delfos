#include <string>
#include <thread>

#include "http.hpp"
#include "asar.hpp"
#include "webview.h"

namespace server {
  bool quit = false;
  int port = 0;

  void Server(Asar * resources, webview::webview * webview) {
    HTTP::Server t(
    [&](HTTP::Request req, HTTP::Response * res) {     
      if (req.method == "GET" && req.path == "/") { 
        res->body = resources->content("/index.html");
        res->headers.insert({"Content-Type", "text/html"});
        return;
      }

      if (req.method == "GET" && resources->exist(req.path)) {
          res->body = resources->content(req.path);
          res->headers.insert({"Content-Type", HTTP::mime_by_extname(req.path)});
          return; 
      }

      res->code = 404;    
    },
    port,
    &port
    );
 
    webview->navigate("http://localhost:" + std::to_string(port));
    t.listen(&quit);
  }
}
