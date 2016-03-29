"use strict";

const intrinsics = require('intrinsics')

console.log('intrinsics', intrinsics);

const flags16 = new Uint8Array(16);
const flags = new Int32Array(flags16.buffer);

intrinsics.__cpuidex(flags16, 0, 0);
const numIDs = flags[0];

for (let i = 0; i <= numIDs; i++) {
	intrinsics.__cpuidex(flags16, i, 0);
	console.log('__cpuidex(flags16, ' + i + ', 0): ', flags);
}

const buf8 = new Uint8Array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]);
const buf32 = new Int32Array(buf8.buffer);

for (let i = 0; i < 100; i++) {
	intrinsics._InterlockedIncrement(buf8);
}
console.log(buf32);