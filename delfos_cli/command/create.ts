import fs from "fs";

const DELFOS_CONFIG_TEMPLATE = `{
  "resources": "./dist",
  "dev_tools": false,
  "window": {
    "title": "__value__",
    "width": 1280,
    "height": 720,
    "icon": ""
  }
}
`;

export default function(value: string): void {
  if (fs.existsSync("./delfos.config.json")) throw "delfos - delfos.config.json already exist.";
  fs.writeFileSync("./delfos.config.json", DELFOS_CONFIG_TEMPLATE.replace("__value__", value));
}
