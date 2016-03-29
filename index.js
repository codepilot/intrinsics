"use strict";

function loadBinding() {
	try {
		return require('./build/Release/binding.node');
	} catch(err) {
		return require('./build/Debug/binding.node');
	}
}

module.exports = loadBinding();