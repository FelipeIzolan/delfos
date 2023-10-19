#include "httplib.h"
#include <thread>

namespace server {
  int port;

  void Server() {
    httplib::Server server;
    server.set_mount_point("/", "./client");
    port = server.bind_to_any_port("0.0.0.0"); // localhost
    server.listen_after_bind();
  }

  std::thread Init() {
    std::thread s(Server);
    return s;
  }
}
