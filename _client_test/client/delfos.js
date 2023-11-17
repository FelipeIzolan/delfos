var delfos = {};
delfos.database = {};
delfos.database.query = window._db_query;
delfos.database.select = function (table, column, where) {
    var w = where ? " WHERE ".concat(where) : "";
    var s = Array.isArray(column) ? "(" + column.reduce(function (acc, c) { return acc += c + ","; }, "") + ")" :
        column ? "(".concat(column, ")") : "*";
    return delfos.database.query("SELECT ".concat(s, " FROM ").concat(table).concat(w, ";"));
};
delfos.storage = {};
delfos.storage.set = window._storage_set;
delfos.storage.get = window._storage_get;
delfos.storage.del = window._storage_del;
window.delfos = delfos;
window._db_query = undefined;
window._storage_set = undefined;
window._storage_get = undefined;
window._storage_del = undefined;
