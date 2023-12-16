import fs from "fs";

const DELFOS_CONFIG_TEMPLATE = `{
  "resources": "./dist",
  "sql": "./init.sql"
  "dev_tools": false,
  "window": {
    "title": "__value__",
    "width": 1280,
    "height": 720,
    "max_width": null,
    "max_height": null,
    "min_width": null,
    "min_height": null,
    "icon": ""
  }
}
`;

export default function(value: string): void {
  if (fs.existsSync("./delfos.config.json")) throw "delfos -> delfos.config.json already exist.";
  fs.writeFileSync("./delfos.config.json", DELFOS_CONFIG_TEMPLATE.replace("__value__", value));
}
