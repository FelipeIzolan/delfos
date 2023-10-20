#include "httplib.h"
#include <thread>

#include "../util.cpp"
#include "../parser.cpp"

namespace server {
  std::string address;
  
  void Server(struct parser::Asar * resources) {
    httplib::Server server;

    server.set_pre_routing_handler([](const httplib::Request& req, auto& res) {

      if (req.path == "/" && req.method == "GET") {
        res.set_content("<h1>Hello, World!</h1>", "text/html");
        return httplib::Server::HandlerResponse::Handled;
      }

      if (util::is_file(req.path) && req.method == "GET") {
        std::cout << "it's just a fucking file!\n";
      }


      return httplib::Server::HandlerResponse::Unhandled;
    });

    // server.Get("/", [&](const httplib::Request& req, httplib::Response& res) {
    //   res.set_content(html, "text/html");
    // });



    int port = server.bind_to_any_port("0.0.0.0");
    address = "http://localhost:" + std::to_string(port);
    server.listen_after_bind();
  }


  std::thread Init(struct parser::Asar * resources) {
    std::thread s(Server, resources);
    return s;
  }
}
