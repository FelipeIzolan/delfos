#pragma once

#include "json.hpp"
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


}
