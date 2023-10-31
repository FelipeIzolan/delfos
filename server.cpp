#include <thread>
#include <string>
#include <sqlite3.h>

#include "../util.cpp"
#include "httpserver.hpp"
#include "asar.hpp"


namespace server {
  void Server(struct Asar::asar * resources, int port) {
    HTTP::Server t;

    t.setup([&](HTTP::Request req, HTTP::Response * res) {     
      // ------- STATIC ------- //
      if (req.method == "GET" && req.path == "/") { 
        res->body = Asar::content(resources, "resources.asar", {"index.html"});
        res->headers.insert({"Content-Type", "text/html"});
        return;
      }

      if (req.method == "GET" && util::is_file(req.path)) {
        std::vector<std::string> p = util::resolve_req_path(req.path);
        if (Asar::exist(resources, p)) {
          res->body = Asar::content(resources, "resources.asar", p);
          res->headers.insert({"Content-Type", HTTP::mimeByExt(util::extname(req.path))});
          return; 
        }
      }

      res->code = 404;    
    });

    t.listen(port);
  }

  std::thread Init(struct Asar::asar * resources, int port) {
    std::thread s(Server, resources, port);
    return s;
  }

}
