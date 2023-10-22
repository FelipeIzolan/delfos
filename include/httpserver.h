#pragma once

#include <cstdlib>
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
  
  class Request {
    public:
      std::map<std::string, std::string> headers;
      std::string method;
      std::string body;
      std::string path;

      Request(char * buffer) {
        std::stringstream p(buffer);
        std::string line;
        bool start = true;

        while (std::getline(p, line)) {
          if (start) {
            int s1 = line.find(" ");
            int s2 = line.find(" ", s1);

            method = line.substr(0, s1);
            path = line.substr(s2+1,s1-1);

            start = false;
            continue;
          }
          
          int sep = line.find(":");
          if (sep == std::string::npos) break; // empty-line
          
          std::string key = line.substr(0, sep);
          std::string value = line.substr(sep+2);
          headers.insert({key, value});
        }

        p >> body;
        std::cout << "body: " << body << "\n";

      }
  };


  class Server {
    public:
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

        int csocket;      
        struct sockaddr_in caddress;
        socklen_t csize = sizeof(caddress);

        if ((csocket = accept(ssocket, (struct sockaddr *)&caddress, &csize)) < 0) {
          perror("http.h -> accept failed.");
          exit(1);
        }

        char * buffer = new char[BUFSIZ];
        ssize_t buffer_size;

        buffer_size = read(csocket, buffer, BUFSIZ);
        Request req(buffer); 

        write(csocket, "a", 1);
        close(csocket);
        close(ssocket);
        delete[] buffer;
    }
  };



}
