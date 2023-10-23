#pragma once

#include <cstdio>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <map>
#include <sstream>
#include <stdio.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

// *htons
// ** convert host-byte-order to network-byte-order
// ** int-bytes to big-endian order.
// *** 3 1 2
// *** 1 2 3

namespace http {
  const std::string ResponseTemplate = "HTTP/1.1 200 OK\r\n"\
                                       "Content-Type: text/html\r\n"\
                                       "\r\n"\
                                       "<!DOCTYPE html><html><body><h1>Hello, my friend!</h1></body></html>";
                                       

  class Request {
    public:
      std::map<std::string, std::string> headers;
      std::string method;
      std::string body;
      std::string path;

      Request(char * buffer) {
        std::stringstream p(buffer);

        for (int i = 0; i < 33; i++) { // max-header = 32
          std::string line;
          std::getline(p, line);

          if (i == 0) {
            int s1 = line.find(" ");
            int s2 = line.find(" ", s1);

            method = line.substr(0, s1);
            path = line.substr(s2+1,s1-1);

            continue;
          }
          
          int sep = line.find(":");
          if (sep == std::string::npos) break; // empty-line
          
          std::string key = line.substr(0, sep);
          std::string value = line.substr(sep+2);

          headers.insert({key, value});
        }

        p >> body;
      }
  };

  class Response {
    public:
      std::map<std::string, std::string> headers;
      std::string body;
      int code = 200;
  };


  class Server {
    

    public:
      void setup(void(*func)(Request, Response*)) {
        handler = func;
      }

      void listen(uint16_t port) {
        int ssocket;
        int soption;
        struct sockaddr_in saddress;
        socklen_t ssize = sizeof(saddress);

        saddress.sin_port = htons(port);
        saddress.sin_addr.s_addr = INADDR_ANY;
        saddress.sin_family = AF_INET;

        if ((ssocket = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
          perror("http.h -> socket failed.");
          exit(1);
        }

        if (setsockopt(ssocket, SOL_SOCKET, SO_REUSEADDR, &soption, sizeof(soption))) {
          perror("http.h -> socket option failed.");
          exit(1);
        }
    
        if (bind(ssocket, (struct sockaddr *)&saddress, ssize) < 0) {
          perror("http.h -> bind failed.");
          exit(1);
        };

        if (::listen(ssocket, SOMAXCONN) < 0) {
          perror("http.h -> listen failed.");
          exit(1);
        }

        while (1) {
          int csocket;      
          struct sockaddr_in caddress;
          socklen_t csize = sizeof(caddress);

          if ((csocket = accept(ssocket, (struct sockaddr *)&caddress, &csize)) < 0) {
            perror("http.h -> accept failed.");
            continue;
          }

          char * buffer = new char[BUFSIZ];
          ssize_t buffer_size = read(csocket, buffer, BUFSIZ);
        
          // Request req(buffer); 
          // Response res;
          // handler(req, &res);
       
          send(csocket, ResponseTemplate.c_str(), ResponseTemplate.length(), 0);


          close(csocket);
        }

        close(ssocket);
    }

    protected:
      std::function<void(Request, Response*)> handler;

  };



}
