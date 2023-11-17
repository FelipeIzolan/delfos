#include <fstream>
#include <iostream>
#include <json.hpp>

class Storage {
  public:
    Storage(const std::string _filename) {
      filename = _filename;
      
      std::ifstream x(filename);
      std::ostringstream y;

      if (x.is_open()) {
        y << x.rdbuf();
        data = json::JSON::Load(y.str());
        std::cout << data["Rob"] << "\n";
      }

      x.close();
    }

    std::string get(std::string key) { 
      return data[key].stringify();
    }
    
    void set(std::string key, json::JSON value) { 
      data[key] = value;
    }
    
    void del(std::string key) {
      data[key] = "undefined";
    }

    void close() {
      std::ofstream x(filename);
      x << data;
      x.close();
    }

  protected:
    std::string filename;
    json::JSON data;
};
