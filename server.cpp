#include <atomic>
#include <string>
#include <thread>

#include "http.hpp"
#include "asar.hpp"

namespace server {
  std::atomic<bool> quit(false);

  void Server(Asar * resources, int port) {
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
    port
    );
 
    t.listen(&quit);
  }

  std::thread Init(Asar * resources, int port) {
    std::thread s(Server, resources, port);
    return s;
  }
}
