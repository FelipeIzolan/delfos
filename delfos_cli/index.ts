#! /usr/bin/env node

import os from "os";
import path from "path";
import process from "process";

import create from "./command/create";
import build from "./command/build";

const arg = process.argv.slice(2);
const value = arg[1];
const command = arg[0];

const platform = os.platform();
const root = path.resolve(process.argv[1], "../");

switch (command) {
  case "create": create(value); break;
  case "build": build(platform, root); break;
}
