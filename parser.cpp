#pragma once

#include <cstdint>
#include <fstream>
#include <sstream>
#include <string>

#include "./util.cpp"
#include "json.hpp"

namespace parser {   
  
  struct Asar {
    json::JSON header;
    int offset;
  };

  auto JSON(std::string j) {
    return json::JSON::Load(j);
  }

  // asar_format: | UInt32: header_size | String: header | Bytes: file1 | ... | Bytes: file42 |
  // https://github.com/electron/asar
  // ---------------------------------
  // Special thanks to Maks-s!
  // https://github.com/Maks-s/asar-cpp
  void Asar(Asar * asar) {
    std::ifstream stream("resources.asar");

    char *size = new char[8];
    stream.read(size, 8);

    uint32_t uSize = *(uint32_t*)(size + 4) - 8;

    char *buffer = new char[uSize + 1];
    buffer[uSize] = '\0';

    stream.seekg(16);
    stream.read(buffer, uSize);

    asar->header = JSON(buffer);
    asar->offset = uSize + 16;

    delete[] size;
    delete[] buffer;
    stream.close();
  }

  std::string AsarContent(struct Asar * asar, std::string key) {
    std::vector<std::string> v = util::resolve_req_path(key);
    auto * k = &asar->header.at("files");

    for (auto i = v.begin(); i != v.end(); i++) {
      std::string t = *i;

      if (util::is_file(t)) k = &k->at(t);
      else { k = &k->at(t); k = &k->at("files"); }
    };

    uint64_t size = (uint64_t) k->at("size").ToInt();
    uint64_t offset = std::stoull(k->at("offset").ToString());
   
    // Probably it's the worst way to resolve this problem
    // Because it read the entire file starting from offset + asar->offset
    // And after read it just cut string using the size.

    // I think that if limit streamsize or stop stream after reach the limit_size
    // is better but I don't know how to do this.

    // Well at least it's working XD
    std::stringstream content;
    std::ifstream stream("resources.asar");

    stream.seekg(offset + asar->offset);
    content << stream.rdbuf();

    stream.close();

    return content.str().substr(0,size);  
  }
}
