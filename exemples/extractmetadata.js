const Popplonode = require('../index.js'),
poppl = new Popplonode();

// Load a pdf sample
poppl.load('test/data/test.pdf');

let metadata = poppl.getMetadata();
console.log(metadata);