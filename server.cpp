#include <thread>
#include <string>
#include <sqlite3.h>

#include "../util.cpp"
#include "http.hpp"
#include "asar.hpp"


namespace server {
  void Server(struct Asar * resources, int port) {
    HTTP::Server t;

    t.setup([&](HTTP::Request req, HTTP::Response * res) {     
      if (req.method == "GET" && req.path == "/") { 
        res->body = resources->content("/index.html");
        res->headers.insert({"Content-Type", "text/html"});
        return;
      }

      if (req.method == "GET" && resources->exist(req.path)) {
          res->body = resources->content(req.path);
          res->headers.insert({"Content-Type", util::extname(HTTP::mimeByExt(req.path))});
          return; 
      }

      res->code = 404;    
    });

    t.listen(port);
  }

  std::thread Init(struct Asar * resources, int port) {
    std::thread s(Server, resources, port);
    return s;
  }

}
