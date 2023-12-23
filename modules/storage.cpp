#include "webview.h"
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
      }

      x.close();
    }

		~Storage() {
      std::ofstream x(filename);
      x << data;
      x.close();
    }

    std::string get(const std::string key) { 
      return data[key].stringify();
    }
    
    void set(const std::string key, json::JSON value) { 
      data[key] = value;
    }
    
    void del(const std::string key) {
      data[key] = "undefined";
    }

  protected:
    std::string filename;
    json::JSON data;
};

void storage_webview_loader(webview::webview * webview, Storage * storage) {
  webview->bind("_storage_set", [storage](const std::string params) {
    json::JSON p = json::JSON::Load(params);
    storage->set(p[0].ToString(), p[1]);
    return "ok";
  });

  webview->bind("_storage_get", [storage](std::string param) {
    std::string key = json::JSON::Load(param)[0].ToString();
    return storage->get(key);
  });

  webview->bind("_storage_del", [storage](std::string param) {
    std::string key = json::JSON::Load(param)[0].ToString();
    storage->del(key);
    return "ok";   
  });
}
