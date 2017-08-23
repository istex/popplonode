const Popplonode = require('../index.js');
const pdf = new Popplonode();
console.log(pdf.load('data/test.pdf'));
console.log(pdf.getMetadata());
