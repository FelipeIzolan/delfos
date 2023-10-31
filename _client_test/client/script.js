"use strict";
var delfos = {};
delfos.database = {};
delfos.database.query = window._query;
delfos.database.select = function (table, column, where) {
    var w = where ? " WHERE ".concat(where) : "";
    var s = Array.isArray(column) ?
        ("(" + column.reduce(function (acc, c) { return acc += c + ","; }, "") + ")") :
        column ? "(".concat(column, ")") :
            "*";
    return delfos.database.query("SELECT ".concat(s, " FROM ").concat(table).concat(w, ";"));
};
window._query = undefined;
window.delfos = delfos;
