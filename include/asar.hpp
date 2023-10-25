#pragma once

#include <json.hpp>
#include <fstream>
#include <vector>

namespace Asar {
  struct asar {
    json::JSON header;
    int offset;
  };
 
  void parser(struct asar * s);
  std::string content(struct asar * s, std::vector<std::string> path);
  bool exist(struct asar * s, std::vector<std::string> path);
}

namespace Asar { 
  // https://github.com/electron/asar
  // ---------------------------------
  // Thanks Maks-s!
  // https://github.com/Maks-s/asar-cpp
  void parser(struct asar * s) {
    std::ifstream stream("resources.asar");

    char *size = new char[8];
    stream.read(size, 8);

    uint32_t uSize = *(uint32_t*)(size + 4) - 8;

    char *buffer = new char[uSize + 1];
    buffer[uSize] = '\0';

    stream.seekg(16);
    stream.read(buffer, uSize);

    s->header = json::JSON::Load(buffer);
    s->offset = uSize + 16;

    delete[] size;
    delete[] buffer;
    stream.close();
  }

  std::string content(struct asar * s, std::vector<std::string> path) {
    auto * k = &s->header.at("files");

    for (auto i = path.begin(); i != path.end(); i++) {
      std::string t = *i;
      size_t e = t.find_last_of(".");

      if (e != std::string::npos && e < t.length()) k = &k->at(t); // is_file
      else { k = &k->at(t); k = &k->at("files"); } // is_directory
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

    stream.seekg(offset + s->offset);
    content << stream.rdbuf();

    stream.close();

    return content.str().substr(0,size);  
  }

  bool exist(struct asar * s, std::vector<std::string> path) {
    auto * k = &s->header.at("files");

    for (auto i = path.begin(); i != path.end(); i++) {
      std::string t = *i;
      size_t e = t.find_last_of(".");

      if (e != std::string::npos && e < t.length()) k = &k->at(t); // is_file
      else { k = &k->at(t); k = &k->at("files"); } // is_directory
    };

    return !k->IsNull();
  }
}
