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
    http::Server t;
    
    t.setup([](http::Request req, http::Response * res) {
      res->body = "<h1>Hello, World!</h1>";
      res->headers.insert({"Content-Type", "text/html"});
    });
    
    t.listen(9999);
  }


  std::thread Init(struct parser::Asar * resources) {
    std::thread s(Server, resources);
    return s;
  }
}
