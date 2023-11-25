import fs from "fs";

const DELFOS_CONFIG_TEMPLATE = `{
  "resources": "./dist",
  "window": {
    "title": "__value__",
    "width": 800,
    "height": 600,
    "icon": ""
  },
  "server": {
    "port": ${Math.round(Math.random() * 65535)}
  }
}
`;

export default function(value: string): void {
  if (fs.existsSync("./delfos.config.json")) throw "delfos - delfos.config.json already exist.";
  fs.writeFileSync("./delfos.config.json", DELFOS_CONFIG_TEMPLATE.replace("__value__", value));
}
