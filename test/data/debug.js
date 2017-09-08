const Popplonode = require('../../index.js');
const poppl = new Popplonode();
poppl.load('test/data/warning.pdf');
poppl.debug = true;
poppl.getTextFromPage(1, (error, content) => {
  if (error) console.log(error);
});
