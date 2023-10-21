import asar from "@electron/asar";
import fs from "fs";

const config = JSON.parse(fs.readFileSync("./delfos.config.json"));
fs.cpSync("./delfos.config.json", config.app + "/delfos.config.json");
asar.createPackage(config.app, "../build/resources.asar");
//
// var allFiles = [];
// var staticFiles = [];
// var directories = [];
//
// function findFiles(filders, dir) {
//   for (const f of filders) {
//     let _Path = dir + `/${f}`;
//     let _Stat = fs.statSync(_Path);
//     
//
//     if (_Stat.isFile()) allFiles.push(_Path);
//     if (_Stat.isDirectory()) { 
//       findFiles(fs.readdirSync(_Path), _Path); 
//       directories.push(_Path); 
//     }
//   }
// }
//
// findFiles(fs.readdirSync(config.app), config.app);
//
// allFiles = allFiles.filter(x => {
//   let ext = path.extname(x);
//   if (ext == ".js" || ext == ".css" || ext == ".html") {
//     staticFiles.push(x);
//     return false;
//   };
//
//   return true;
// });
//
//
// for (const d of directories) {
//   let dir = d.replace("./client", "../build");
//
//   if (!fs.existsSync(dir)) {
//     fs.mkdirSync(dir.replace("./client", "../build"));
//   }
// }
//
// for (const f of allFiles) {
//   let out = f.replace("./client", "../build");
//   fs.copyFileSync(f, out);
// }
