import fs from "fs";

import asar from "@electron/asar";
import resources_hacker from "@erhhung/node-resource-hacker";
import { load as cheerio } from "cheerio";

async function SDK(platform: NodeJS.Platform) {
  // Download SDK
  // https://api.github.com/repos/felipeizolan/delfos/releases/latest
  if (!fs.existsSync(`./.sdk/delfos${platform == "win32" ? ".exe" : ""}`)) {
    fs.cpSync("/home/felipeizolan/Documents/delfos/build/delfos", `./.sdk/delfos${platform == "win32" ? ".exe" : ""}`);
  }

  if (!fs.existsSync("./.sdk/delfos.js")) {
    let raw: Response | string = await fetch("https://raw.githubusercontent.com/FelipeIzolan/delfos/main/delfos_cli/delfos.js");
    raw = await raw.text();
    fs.writeFileSync("./.sdk/delfos.js", raw);
  }
}

function FOLDER(title: string) {
  fs.mkdirSync("./.sdk", { recursive: true });
  fs.mkdirSync(`./${title}-app`, { recursive: true });
  fs.mkdirSync(`./${title}-app/data`, { recursive: true });
}

async function BUILD(platform: NodeJS.Platform, resources: string, title: string) {
  let html = fs.readFileSync(`${resources}/index.html`, { encoding: "utf8" });
  let lib = fs.readFileSync(`./.sdk/delfos.js`, { encoding: "utf8" });
  let $ = cheerio(html);

  $("head").append(`<script>${lib}</script>`);

  fs.writeFileSync(`${resources}/index.html`, $.html());

  fs.cpSync(`./.sdk/delfos${platform == "win32" ? ".exe" : ""}`, `./${title}-app/${title}${platform == "win32" ? ".exe" : ""}`);
  fs.cpSync("./delfos.config.json", `${resources}/delfos.config.json`);
  await asar.createPackage(resources, `./${title}-app/resources.asar`);
  fs.writeFileSync(`${resources}/index.html`, html);
}

async function icon(path: string, platform: string, pbin: string) {
  if (platform == "win32" && fs.existsSync(path)) 
    await resources_hacker({
      action: "addoverwrite",
      open: pbin,
      save: pbin,
      resource: path,
      mask: {
        type: "ICONGROUP",
        name: "MAINICON"
      }
  });
}

export default async function(platform: NodeJS.Platform) {
  if (!fs.existsSync("./delfos.config.json")) throw "delfos -> delfos.config.json not found.";

  const config = JSON.parse(fs.readFileSync("./delfos.config.json", { encoding: "utf8" }));
  
  FOLDER(config.window.title);
  await SDK(platform);
  BUILD(platform, config.resources, config.window.title);
}
