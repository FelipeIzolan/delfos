var delfos = {};
delfos.database = {};
delfos.database.query = window._db_query;
delfos.database.select = function (table, column, where) {
    var w = where ? " WHERE ".concat(where) : "";
    var s = Array.isArray(column) ? "(" + column.reduce(function (acc, c) { return acc += c + ","; }, "") + ")" :
        column ? "(".concat(column, ")") : "*";
    return delfos.database.query("SELECT ".concat(s, " FROM ").concat(table).concat(w, ";"));
};
window.delfos = delfos;
window._db_query = undefined;
console.log(delfos.database.query);
