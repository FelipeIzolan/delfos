"use strict";

const delfos = {};
window.delfos = delfos;

delfos.database = {};
delfos.database.query = window._db_query;
delfos.database.delete = function (table, where) {
    let w = where ? ` WHERE ${where}` : "";
    return this.query(`DELETE FROM ${table}${w}`);
};
delfos.database.select = function (table, columns, where) {
    let w = where ? ` WHERE ${where}` : "";
    let s = columns ? `(${columns})` : "*";
    return this.query(`SELECT ${s} FROM ${table}${w};`);
};
delfos.database.insert = function (table, values, columns) {
    let s = columns ? ` (${columns})` : "";
    let v = Array.isArray(values[0]) ?
        values.map(x => `(${x.map(y => typeof y == "string" ? `'${y}'` : y)})`)
        : `(${values})`;
    return this.query(`INSERT INTO ${table}${s} VALUES ${v};`);
};

delfos.storage = {};
delfos.storage.set = window._storage_set;
delfos.storage.get = window._storage_get;
delfos.storage.del = window._storage_del;

delfos.window = {};
delfos.window.setTitle = window._window_set_title;
delfos.window.setPosition = window._window_set_position;
delfos.window.setSize = window._window_set_size;
delfos.window.maximize = window._window_maximize;
delfos.window.minimize = window._window_minimize;
delfos.window.restore = window._window_restore;

window._db_query = undefined;
window._storage_set = undefined;
window._storage_get = undefined;
window._storage_del = undefined;
window._window_set_title = undefined;
window._window_set_position = undefined;
window._window_set_size = undefined;
window._window_maximize = undefined;
window._window_minimize = undefined;
window._window_restore = undefined;
