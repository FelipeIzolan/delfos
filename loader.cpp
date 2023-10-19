#include <cstdint>
#include <fstream>
#include <iostream>

#include "rapidjson/document.h"

namespace loader {
  int headerOffset;
  
  std::ifstream openAsarFile(const char * path) {
    std::ifstream a;  
    
    try {
      a.open(path);
      if (!a) throw "app.asar not found.";
    } catch(const char* err) {
      std::cout << err << "\n";
    }
    
    return a;
  }

  // asar_format: | UInt32: header_size | String: header | Bytes: file1 | ... | Bytes: file42 |
  // https://github.com/electron/asar
  // ---------------------------------
  // Special thanks to Maks-s!
  // https://github.com/Maks-s/asar-cpp
  char *parseAsarHeader(std::ifstream * asar) { 
    char *p = new char[8];
    asar->read(p, 8); // get header_size
    uint32_t uSize = *(uint32_t*)(p + 4) - 8;
    headerOffset = uSize + 16;
    delete[] p;

    char *buffer = new char[uSize + 1];
    buffer[uSize] = '\0'; // null_char
    
    asar->seekg(16); // skip header_size
    asar->read(buffer, uSize);

    return buffer;
  }

  char *parseAsarContent(std::ifstream * asar, int size, int offset) {
    char * content = new char[size + 1];
    content[size] = '\0';
    asar->seekg(offset+headerOffset);
    asar->read(content, size);
    return content;
  }

  rapidjson::Document parseJson(const char *json) {
    rapidjson::Document object;
    object.Parse(json); 
    delete[] json; // free string after being used to build Json.
    return object;
  }

  void load() {
    std::ifstream asar = openAsarFile("./app.asar");
    rapidjson::Document object = parseJson(parseAsarHeader(&asar));
 
    unsigned int html_size = object["files"]["index.html"]["size"].GetUint();
    unsigned int html_offset = std::stoi(object["files"]["index.html"]["offset"].GetString()); // offset is string, so needs to be converted;
    
    char * html = parseAsarContent(&asar, html_size, html_offset);
    std::cout << "html: " << html <<"\n\n";

    asar.close();
  }
};
