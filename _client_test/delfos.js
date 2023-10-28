const delfos = {};

delfos.query = function (query) {
  return fetch("/delfos/query", { method: "POST", body: query });
}
