#include <thread>
#include <string>
#include <sqlite3.h>

#include "httpserver.hpp"
#include "asar.hpp"

#include "../util.cpp"
#include "../sqlite.cpp"

namespace server {
  void Server(struct Asar::asar * resources, SQLite * db, int port) {
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

      // ------- DATABASE ------- //
      if (req.method == "POST" && req.path == "/delfos/query") {
        // std::cout << req.body << "\n";
        // std::cout << (db->exec(req.body)).stringify() << "\n";
        
        // res->body = (db->exec(req.body)).stringify();
        // res->headers.insert({"Content-Type", "application/json"});
        std::cout << "Hi from database controller\n";
        return;
      }

      res->code = 404;
    
    });


    t.listen(port);
  }


  std::thread Init(struct Asar::asar * resources, SQLite * db, int port) {
    std::thread s(Server, resources, db, port);
    return s;
  }
}
