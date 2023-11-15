#include <fstream>
#include <json.hpp>

class Storage {
  public:
    Storage(const std::string _filename) {
      filename = _filename;
      
      std::ifstream x(filename);
      std::stringstream y;

      if (!x.fail()) { 
        y << x.rdbuf();
        data.Load(y.str());
      }

      x.close();
    }

    std::string get(std::string key) {
      return data[key].stringify();
    }

    void set(std::string key, std::string value) {
      data[key] = value;
    }

    void del(std::string key) {
      data[key] = "undefined";
    }

    void close() {
      std::ofstream x(filename);
      x << data.stringify();
      x.close();
    }

  protected:
    std::string filename;
    json::JSON data;
};
