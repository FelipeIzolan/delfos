#include <webview.h>
#include <json.hpp>
#include <asar.hpp>

#include "modules/database.cpp"
#include "modules/storage.cpp"
#include "modules/window.cpp"
#include "modules/system.cpp"

#include "server.cpp"

void init_config(json::JSON config, webview::webview * webview, Window * window) {
  webview->set_title(config["window"]["title"].ToString());
  webview->set_size(config["window"]["width"].ToInt(), config["window"]["height"].ToInt(), WEBVIEW_HINT_NONE);

  if (!config["window"]["min_width"].IsNull() && !config["window"]["min_height"].IsNull())
    webview->set_size(config["window"]["min_width"].ToInt(), config["window"]["min_height"].ToInt(), WEBVIEW_HINT_MIN);

  if (!config["window"]["max_width"].IsNull() && !config["window"]["max_height"].IsNull())
    webview->set_size(config["window"]["max_width"].ToInt(), config["window"]["max_height"].ToInt(), WEBVIEW_HINT_MAX);
	
	window->set_icon(config["window"]["icon"].ToString());
}

int main() {   
  Asar resources("resources.asar");
  
	json::JSON * config = new json::JSON;
	*config = json::JSON::Load(resources.content("/delfos.config.json"));

  webview::webview webview(config->at("dev_tools").ToBool(), nullptr);

  Database database("./data/.database.sql");
  Storage storage("./data/.storage.json");
  Window window(webview.window()); 
  System system;

  database_webview_loader(&webview, &database);
  storage_webview_loader(&webview, &storage);
  window_webview_loader(&webview, &window);
  system_webview_loader(&webview, &system);
  
  std::thread thread(server::Server, &resources, &webview);
  
  init_config(*config, &webview, &window);
  delete config;

	webview.run();

  server::quit = true;
  thread.join();

  return 0;
}

