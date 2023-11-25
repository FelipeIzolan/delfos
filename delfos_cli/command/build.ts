import fs from "fs";

import asar from "@electron/asar";
import resources_hacker from "@erhhung/node-resource-hacker";
import { load as cheerio } from "cheerio";

function downloadSDK(path: string) {
  fs.mkdirSync("./.sdk", { recursive: true });
  fs.cpSync("C:/Users/F3/Documents/delfos/build/delfos.exe", path);
  // Download SDK
  // https://api.github.com/repos/felipeizolan/delfos/releases/latest
}

function folder(path: string) {
  fs.mkdirSync(`${path}`, { recursive: true });
  fs.mkdirSync(`${path}/data`, { recursive: true });
}

async function build(resources: string, pout: string, psdk: string, pbin: string, root: string) {
  if (!fs.existsSync(psdk)) downloadSDK(psdk);

  let html = fs.readFileSync(`${resources}/index.html`, { encoding: "utf8" });
  let lib = fs.readFileSync(`${root}/delfos.js`, { encoding: "utf8" });
  let $ = cheerio(html);

  $("head").append(`<script>${lib}</script>`);

  fs.writeFileSync(`${resources}/index.html`, $.html());

  fs.cpSync(psdk, pbin);
  fs.cpSync("./delfos.config.json", resources + "/delfos.config.json");
  await asar.createPackage(resources, `${pout}/resources.asar`);

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

export default async function(platform: NodeJS.Platform, root: string) {
  if (!fs.existsSync("./delfos.config.json")) throw "delfos - delfos.config.json not found.";

  const config = JSON.parse(fs.readFileSync("./delfos.config.json", { encoding: "utf8" }));
  const out = `./${config.window.title}-app`;
  const sdk = `./.sdk/delfos${platform == "win32" ? ".exe" : ""}`;
  const bin = `${out}/${config.window.title}${platform == "win32" ? ".exe" : ""}`;

  folder(out);
  build(config.resources, out, sdk, bin, root);
  icon(config.window.icon, platform, bin);
}
