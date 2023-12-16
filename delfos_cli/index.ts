#! /usr/bin/env node

import os from "os";
import process from "process";

import create from "./command/create";
import build from "./command/build";

const arg = process.argv.slice(2);
const value = arg[1];
const command = arg[0];
const platform = os.platform();

if (command == "") throw "delfos -> Invalid command."

switch (command) {
  case "create": create(value); break;
  case "build": build(platform); break;
}
