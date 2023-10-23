#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstring>
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

namespace HTTP {
  inline std::string statusMessage(int code) {
	  switch (code) {
	  case 100: return "Continue";
	  case 101: return "Switching Protocols";
	  case 102: return "Processing";
	  case 103: return "Early Hints";
	  case 200: return "OK";
	  case 201: return "Created";
	  case 202: return "Accepted";
	  case 203: return "Non-Authoritative Information";
	  case 204: return "No Content";
	  case 205: return "Reset Content";
	  case 206: return "Partial Content";
	  case 207: return "Multi-Status";
	  case 208: return "Already Reported";
	  case 226: return "IM Used";
	  case 300: return "Multiple Choices";
	  case 301: return "Moved Permanently";
	  case 302: return "Found";
	  case 303: return "See Other";
	  case 304: return "Not Modified";
	  case 305: return "Use Proxy";
	  case 307: return "Temporary Redirect";
	  case 308: return "Permanent Redirect";
	  case 400: return "Bad Request";
	  case 401: return "Unauthorized";
	  case 402: return "Payment Required";
	  case 403: return "Forbidden";
	  case 404: return "Not Found";
	  case 405: return "Method Not Allowed";
	  case 406: return "Not Acceptable";
	  case 407: return "Proxy Authentication Required";
	  case 408: return "Request Timeout";
	  case 409: return "Conflict";
	  case 410: return "Gone";
	  case 411: return "Length Required";
	  case 412: return "Precondition Failed";
	  case 413: return "Content Too Large";
	  case 414: return "URI Too Long";
	  case 415: return "Unsupported Media Type";
	  case 416: return "Range Not Satisfiable";
	  case 417: return "Expectation Failed";
	  case 418: return "I'm a teapot";
	  case 421: return "Misdirected Request";
	  case 422: return "Unprocessable Content";
	  case 423: return "Locked";
	  case 424: return "Failed Dependency";
	  case 425: return "Too Early";
	  case 426: return "Upgrade Required";
	  case 428: return "Precondition Required";
	  case 429: return "Too Many Requests";
	  case 431: return "Request Header Fields Too Large";
	  case 451: return "Unavailable For Legal Reasons";
	  case 500: return "Internal Server Error";
	  case 501: return "Not Implemented";
	  case 502: return "Bad Gateway";
	  case 503: return "Service Unavailable";
	  case 504: return "Gateway Timeout";
	  case 505: return "HTTP Version Not Supported";
	  case 506: return "Variant Also Negotiates";
	  case 507: return "Insufficient Storage";
	  case 508: return "Loop Detected";
	  case 510: return "Not Extended";
	  case 511: return "Network Authentication Required";
	  default: return std::string();
	  }
  }

  inline std::string headers(std::map<std::string, std::string> h) {
    std::string s = "";
    
    for (auto i = h.begin(); i != h.end(); i++) {
      s += i->first + ": " + i->second + "\r\n";
    }

    return s;
  }
}


namespace HTTP {

  class Request {
    public:
      std::map<std::string, std::string> headers;
      std::string method;
      std::string body;
      std::string path;

      Request(char * buffer) {
        std::stringstream p(buffer);

        for (int i = 0; i < 99; i++) { // https://developer.mozilla.org/en-US/docs/Web/HTTP/Headers
          std::string line;
          std::getline(p, line);

          if (i == 0) {
            int s1 = line.find(" ");
            int s2 = line.find("HTTP");

            method = line.substr(0, s1);
            path = line.substr(s1+1,s2-5);

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
      void setup(std::function<void(Request, Response*)> func) { handler = func; }

      void listen(uint16_t port) {
        int ssocket;
        int soption;
        struct sockaddr_in saddress;
        socklen_t ssize = sizeof(saddress);

        saddress.sin_port = htons(port); // network-byte-order - big-endian
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

          char * cbuffer = new char[BUFSIZ];
          ssize_t cbuffer_size = read(csocket, cbuffer, BUFSIZ);
       
          char * sbuffer = new char[BUFSIZ];

          Request req(cbuffer); 
          Response res;

          handler(req, &res); 
          std::snprintf(sbuffer, BUFSIZ, ResponseTemplate.c_str(), res.code, statusMessage(res.code).c_str(), headers(res.headers).c_str(), res.body.c_str());
          
          send(csocket, sbuffer, strlen(sbuffer), 0);

          close(csocket);
          delete[] cbuffer;
          delete[] sbuffer;
        }

        close(ssocket);
    }

    protected:
      std::function<void(Request, Response*)> handler;
      std::string ResponseTemplate = "HTTP/1.1 %i %s\r\n" // http-line
                                     "%s" // headers
                                     "\r\n" // empty-line
                                     "%s"; // body
  };

}
