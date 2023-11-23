#! /usr/bin/env node

import process from "process";

const arg = process.argv.slice(2);
const command = arg.find(x => !x.startsWith("-") && !x.startsWith("--"));

console.log(command);

switch (command) {
  case "create":
    break;
  case "build":
    break;
  case "debug":
    break;
}
