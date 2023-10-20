#include <fstream>
#include <sstream>
#include <string>

#include "./util.cpp"
#include "json.hpp"

#ifndef _PARSERCPP_
#define _PARSERCPP_

namespace parser {   
  
  struct Asar {
    nlohmann::json header;
    std::ifstream stream;
    int offset;
  };

  nlohmann::json JSON(const char *json) {
    return nlohmann::json::parse(json);
  }

  // asar_format: | UInt32: header_size | String: header | Bytes: file1 | ... | Bytes: file42 |
  // https://github.com/electron/asar
  // ---------------------------------
  // Special thanks to Maks-s!
  // https://github.com/Maks-s/asar-cpp
  void Asar(struct Asar * asar, std::string p) {
    asar->stream.open(p, std::ios::binary);

    char *size = new char[8];
    asar->stream.read(size, 8);

    uint32_t uSize = *(uint32_t*)(size + 4) - 8;

    delete[] size;

    char *buffer = new char[uSize + 1];
    buffer[uSize] = '\0';

    asar->stream.seekg(16);
    asar->stream.read(buffer, uSize);

    asar->header = JSON(buffer);
    asar->offset = uSize + 16;

    delete[] buffer;
  }

  std::string AsarContent(struct Asar * asar, std::string key) { 
    std::vector<std::string> v = util::resolve_req_path(key);
    auto k = asar->header["files"];

    for (auto i = v.begin(); i != v.end(); i++) {
      std::string t = *i;

      if (util::is_file(t)) k = k[t.c_str()];
      else k = k[t.c_str()]["files"];
    };

    uint64_t size = k["size"];
    uint64_t offset = std::stoull(std::string(k["offset"]));

    // Probably it's the worst way to resolve this problem
    // Because it read the entire file starting from offset + asar->offset
    // And after read it just cut string using the size.

    // I think that if limit streamsize or stop stream after reach the limit_size
    // is better but I don't know how to do this.
    
    // Well at least it's working XD
    std::stringstream content;
    asar->stream.seekg(offset + asar->offset);
    content << asar->stream.rdbuf();

    return content.str().substr(0,size);
  }
};

#endif
