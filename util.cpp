#pragma once

#include <vector>
#include <string>

namespace util {
  // is_file from httplib::detail::is_file use stat to check
  // it use path, checking if have a extname
  bool is_file(std::string p) {
    size_t i = p.find_last_of(".");
    return i != std::string::npos && i > 0;
  }

  std::string extname(std::string p) {
    return p.substr(p.find_last_of(".")+1);
  }

  char REQ_PATH_SEP[] = "/";
  std::vector<std::string> resolve_req_path(std::string p) {
    std::vector<std::string> v;

    p.erase(p.begin(), p.begin() + 1); // erase first "/"
    int e = p.find(REQ_PATH_SEP);

    while (e != std::string::npos) {
      v.insert(v.end(), p.substr(0, e));
      p.erase(p.begin(), p.begin() + e + 1);
      e = p.find(REQ_PATH_SEP);
    }

    v.insert(v.end(), p.substr(0)); 
    
    return v; 
  } 
}
