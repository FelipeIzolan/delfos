#include <fstream>
#include <iostream>
#include "rapidjson/document.h"

#ifndef _PARSERCPP_
#define _PARSERCPP_

namespace parser {   
  
  struct Asar {
    rapidjson::Document header;
    std::ifstream stream;
    int offset;
  };

  rapidjson::Document JSON(const char *json) {
    rapidjson::Document object;
    object.Parse(json); 
    return object;
  }

  // asar_format: | UInt32: header_size | String: header | Bytes: file1 | ... | Bytes: file42 |
  // https://github.com/electron/asar
  // ---------------------------------
  // Special thanks to Maks-s!
  // https://github.com/Maks-s/asar-cpp
  void Asar(struct Asar * asar, std::string p) {
    asar->stream.open(p);

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
    if (asar->header["files"].HasMember(key.c_str())) {
    // char * content = new char[size + 1];
    // content[size] = '\0';
    //
    // asar->stream.seekg(offset + asar->offset);
    // asar->stream.read(content, size);
    // 
    // return content;
    }
    
    return nullptr; 
  }

};

#endif
