const Popplonode = require('../index.js');
const pdf = new Popplonode();
console.log(pdf.load('data/test.pdf'));
console.log(pdf.getMetadata());
pdf.getTextFromPage(0, (error, text) => {
  if (error) return console.log('error à la dude: ', error);
  console.log('text :', text);
});
