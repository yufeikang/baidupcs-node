const baidupcs = require('bindings')('baidupcs');

const BaiDuPCS = baidupcs();

BaiDuPCS.createPcsHandle("/tmp/ss");

console.log(BaiDuPCS.setError("123"));
