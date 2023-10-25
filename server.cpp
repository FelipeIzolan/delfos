#include <iostream>
#include <thread>
#include <string>

#include "httpserver.hpp"
#include "asar.hpp"

#include "../util.cpp"

namespace server {
  void Server(struct Asar::asar * resources) {
    HTTP::Server t;

    t.setup([&](HTTP::Request req, HTTP::Response * res) {     
      
      if (req.method == "GET" && req.path == "/") { 
        res->body = Asar::content(resources, {"index.html"});
        res->headers.insert({"Content-Type", "text/html"});
        return;
      }


      std::vector<std::string> p = util::resolve_req_path(req.path);
      if (req.method == "GET" && util::is_file(req.path) && Asar::exist(resources, p)) {
        res->body = Asar::content(resources, p);
        res->headers.insert({"Content-Type", HTTP::mimeByExt(util::extname(req.path))});
        return; 
      }

      res->code = 404;
    
    });


    t.listen(9999);
  }


  std::thread Init(struct Asar::asar * resources) {
    std::thread s(Server, resources);
    return s;
  }
}
