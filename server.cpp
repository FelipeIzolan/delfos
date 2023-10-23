#include "httpserver.h"
#include <thread>
#include <string>

#include "../util.cpp"
#include "../parser.cpp"
#include "mime.h"

namespace server {
  std::string address;
  Mime mime;

  void Server(struct parser::Asar * resources) {
    address = "http://localhost:" + std::to_string(9999);
    HTTP::Server t;
    
    t.setup([&](HTTP::Request req, HTTP::Response * res) {
      
      if (req.method == "GET" && req.path == "/") { 
        res->body = parser::AsarContent(resources, "/index.html");
        res->headers.insert({"Content-Type", "text/html"});
      }

      if (req.method == "GET" && util::is_file(req.path)) {
        res->body = parser::AsarContent(resources, req.path);
        res->headers.insert({"Content-Type", mime[util::extname(req.path)]});
      }

    });
    
    t.listen(9999);
  }


  std::thread Init(struct parser::Asar * resources) {
    std::thread s(Server, resources);
    return s;
  }
}
