interface Window {
    _db_query: ((t: string) => Promise<any>)
    delfos: DelfosWindow
}

type DelfosDatabase = {
  query(query: string): Promise<any>,
  select(table: string, column?: string[] | string, where?: string): Promise<any>
}

interface DelfosWindow {
  database: DelfosDatabase
}

const delfos = <DelfosWindow> {};

delfos.database = <DelfosDatabase>{};
delfos.database.query = <(t:string) => Promise<any>> window._db_query;
delfos.database.select = function (table: string, column?: string[] | string, where?: string) {
  let w = where ? ` WHERE ${where}` : "";
  let s = Array.isArray(column) ? "(" + column.reduce((acc, c) => acc += c + ",", "") + ")" :
          column ? `(${column})` : "*";

  return delfos.database.query(`SELECT ${s} FROM ${table}${w};`);
}

window.delfos = delfos;
window._db_query = <any>undefined;

console.log(delfos.database.query);
