#include "httplib.h"
#include <thread>
#include <string>

#include "../util.cpp"
#include "../parser.cpp"
#include "mime.h"

namespace server {
  std::string address;
  Mime mime;

  void Server(struct parser::Asar * resources) {
    httplib::Server server;

    server.set_pre_routing_handler([&](const httplib::Request& req, httplib::Response& res) {

      if (req.path == "/" && req.method == "GET") {
        std::string html = parser::AsarContent(resources, "/index.html");
        res.set_content(html, "text/html");
        
        return httplib::Server::HandlerResponse::Handled;
      }
      
      if (util::is_file(req.path) && req.method == "GET") {
        std::string content = parser::AsarContent(resources, req.path);
        res.set_content(content, mime[util::extname(req.path)]);
        
        return httplib::Server::HandlerResponse::Handled;
      }

      return httplib::Server::HandlerResponse::Unhandled;
    });

    int port = server.bind_to_any_port("0.0.0.0");
    address = "http://localhost:" + std::to_string(port);
    server.listen_after_bind();
  }


  std::thread Init(struct parser::Asar * resources) {
    std::thread s(Server, resources);
    return s;
  }
}
