interface Window {
    _db_query: ((query: string) => Promise<any>)
    _storage_set: ((key: string, value: any) => Promise<string>)
    _storage_get: ((key: string) => Promise<string>)
    _storage_del: ((key: string) => Promise<string>)
    delfos: DelfosWindow
}

type DelfosStorage = {
  set(key: string, value: any): Promise<string>,
  get(key: string): Promise<string>,
  del(key: string): Promise<string>
}

type DelfosDatabase = {
  query(query: string): Promise<any>,
  select(table: string, column?: string[] | string, where?: string): Promise<any>
}

interface DelfosWindow {
  database: DelfosDatabase,
  storage: DelfosStorage
}

const delfos = <DelfosWindow> {};

delfos.database = <DelfosDatabase> {};
delfos.database.query = window._db_query;

delfos.database.select = function (table: string, column?: string[] | string, where?: string) {
  let w = where ? ` WHERE ${where}` : "";
  let s = Array.isArray(column) ? "(" + column.reduce((acc, c) => acc += c + ",", "") + ")" :
          column ? `(${column})` : "*";

  return delfos.database.query(`SELECT ${s} FROM ${table}${w};`);
}

delfos.storage = <DelfosStorage> {};
delfos.storage.set = window._storage_set;
delfos.storage.get = window._storage_get;
delfos.storage.del = window._storage_del;

window.delfos = delfos;

window._db_query = <any>undefined;
window._storage_set = <any>undefined;
window._storage_get = <any>undefined;
window._storage_del = <any>undefined;

console.log(delfos.database.query);
