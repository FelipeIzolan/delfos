import asar from "@electron/asar";
import fs from "fs";

const config = JSON.parse(fs.readFileSync("./delfos.config.json"));
const app = config.app;
delete config.app;

fs.cpSync("./delfos.config.json", app + "/delfos.config.json");

asar.createPackage(app, "../build/resources.asar");
