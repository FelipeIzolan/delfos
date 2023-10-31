#pragma once

#include <vector>
#include <string>

namespace util {
  // it use path to check if have a extname
  bool is_file(std::string p) {
    size_t i = p.find_last_of(".");
    return i != std::string::npos && i > 0;
  }

  std::string extname(std::string p) {
    return p.substr(p.find_last_of(".")+1);
  }

  std::vector<std::string> resolve_req_path(std::string p) {
    std::vector<std::string> v;

    p.erase(0, 1); // erase first "/"
    int e = p.find('/');

    while (e != std::string::npos) {
      v.insert(v.end(), p.substr(0, e));
      p.erase(p.begin(), p.begin() + e + 1);
      e = p.find('/');
    }

    std::string last = p.substr(0);
    size_t query = last.find("?");

    if (query != std::string::npos) v.insert(v.end(), p.substr(0, query));
    else v.insert(v.end(), p.substr(0));

    return v; 
  }
}
