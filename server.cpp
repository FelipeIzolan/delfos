#include "httplib.h"
#include <thread>

namespace server {
  std::string address;
  
  void Server() {
    httplib::Server server;
    int port = server.bind_to_any_port("0.0.0.0");
    address = "http://localhost:" + std::to_string(port);

    server.set_mount_point("/", "./resources");
    server.listen_after_bind();
  }


  std::thread Init() {
    std::thread s(Server);
    return s;
  }
}
