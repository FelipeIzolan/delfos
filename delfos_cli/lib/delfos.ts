import type { DelfosWebview, DelfosDatabase, DelfosStorage, DelfosWindow, SQLiteValues} from "./types";

const delfos = <DelfosWebview> {};
window.delfos = delfos;

// ------------
// I DATABASE I
// ------------
delfos.database = <DelfosDatabase> {};

delfos.database.query = window._db_query;

delfos.database.delete = function (table: string, where?: string) {
  let w = where ? ` WHERE ${where}` : "";
  return this.query(`DELETE FROM ${table}${w}`);
}

delfos.database.select = function (table: string, columns?: string[] | string, where?: string) {
  let w = where ? ` WHERE ${where}` : "";
  let s = columns ? `(${columns})` : "*";
  return this.query(`SELECT ${s} FROM ${table}${w};`);
}

delfos.database.insert = function (table: string, values: SQLiteValues[][] | SQLiteValues[], columns?: string[] | string) {
  let s = columns ? ` (${columns})` : "";
  let v = Array.isArray(values[0]) ? 
          // Format to SQLite TEXT
          values.map(x => `(${(<SQLiteValues[]>x).map(y => typeof y == "string" ? `'${y}'` : y)})`) 
          : `(${values})`;

  return this.query(`INSERT INTO ${table}${s} VALUES ${v};`);
}

// -----------
// I STORAGE I
// -----------
delfos.storage = <DelfosStorage> {};
delfos.storage.set = window._storage_set;
delfos.storage.get = window._storage_get;
delfos.storage.del = window._storage_del;

// ----------
// I WINDOW I
// ----------
delfos.window = <DelfosWindow> {};
delfos.window.setPosition = window._window_set_position;
delfos.window.setSize = window._window_set_size;
delfos.window.maximize = window._window_maximize;
delfos.window.minimize = window._window_minimize;
delfos.window.restore = window._window_restore;

// --------
// I FREE I
// --------
window._db_query = <any>undefined;

window._storage_set = <any>undefined;
window._storage_get = <any>undefined;
window._storage_del = <any>undefined;

window._window_set_position = <any>undefined;
window._window_set_size = <any>undefined;
window._window_maximize = <any>undefined;
window._window_minimize = <any>undefined;
window._window_restore = <any>undefined;
