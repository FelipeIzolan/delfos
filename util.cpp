#include <cstddef>
#include <iostream>
#include <string>

#ifndef _UTILCPP_
#define _UTILCPP_

namespace util {

  bool endswith(std::string t, std::string p) {
    return t.substr(t.size() - p.size()) == p;
  }

  bool is_file(std::string p) {
    size_t i = p.find_last_of(".");
    return i != std::string::npos && i > 0;
  }
  
  std::string extname(std::string p) { 
    if (is_file(p)) return nullptr;
    return p.substr(p.find_last_of("."));
  }

}

#endif
