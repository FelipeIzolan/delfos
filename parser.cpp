#include <cstdint>
#include <fstream>
#include <iostream>

#include "rapidjson/document.h"


namespace parser {   
  
  struct Asar {
    rapidjson::Document header;
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
  Asar asarHeader(std::ifstream * file) { 
    char *p = new char[8];
    file->read(p, 8);
    
    uint32_t uSize = *(uint32_t*)(p + 4) - 8;

    delete[] p;
    
    char *buffer = new char[uSize + 1];
    buffer[uSize] = '\0';
    
    file->seekg(16);
    file->read(buffer, uSize);

    struct Asar a;
    a.header = JSON(buffer);
    a.offset = uSize + 16;

    delete[] buffer;
    
    return a;
  }

  std::string asarContent(std::ifstream * file, int size, int offset, int h_offset) {
    char * content = new char[size + 1];
    content[size] = '\0';

    file->seekg(offset + h_offset);
    file->read(content, size);
    
    return content;
  }

};
