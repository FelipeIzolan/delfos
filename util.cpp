#include <vector>
#include <string>

#ifndef _UTILCPP_
#define _UTILCPP_

namespace util {
  char REQ_PATH_SEP[] = "/";

  bool is_file(std::string p) {
    size_t i = p.find_last_of(".");
    return i != std::string::npos && i > 0;
  }
  
  std::string extname(std::string p) { 
    if (!is_file(p)) return "";
    return p.substr(p.find_last_of("."));
  }

  std::string content_type(std::string p) {
    std::string ext = extname(p);

    if (ext == ".html") return "text/html";
    if (ext == ".js") return "application/javascript";
    if (ext == ".css") return "text/css";

    if (ext == ".png") return "image/png";

    return ext;
  }

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

#endif
