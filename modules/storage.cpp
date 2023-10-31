#include <fstream>
#include <json.hpp>

class Storage {
  public:
    Storage() {
      std::ifstream x(".storage");
      std::stringstream y;

      if (x.fail()) data["__init"] = 1337;
      else { y << x.rdbuf(); data.Load(y.str()); }

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
      std::ofstream x(".storage");
      x << data.stringify();
      x.close();
    }

  protected:
    json::JSON data;
};
