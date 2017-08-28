const Popplonode = require('../index.js');
const expect = require('chai').expect;

describe('popplonode', function () {
  it('should construct an new Popplonode object', function () {
    const poppl = new Popplonode();
    expect(poppl).to.be.instanceOf(Popplonode);
  });

  it('should load a pdf file', function () {
    const poppl = new Popplonode();
    expect(poppl.load('test/data/test.pdf')).to.true;
  });

  it('should get the metadata from pdf file', function () {
    const poppl = new Popplonode();
    poppl.load('test/data/test.pdf');
    const metadata = poppl.getMetadata();
    expect(metadata).to.be.an('object');
    expect(metadata).to.have.own.property('CreationDate');
    expect(metadata.CreationDate).to.be.a('string');
    expect(metadata).to.have.own.property('Author');
    expect(metadata.Author).to.be.a('string');
    expect(metadata).to.have.own.property('Creator');
    expect(metadata.Creator).to.be.a('string');
    expect(metadata).to.have.own.property('Producer');
    expect(metadata.Producer).to.be.a('string');
    expect(metadata).to.have.own.property('ModDate');
    expect(metadata.ModDate).to.be.a('string');
    expect(metadata).to.have.own.property('Title');
    expect(metadata.Title).to.be.a('string');
    expect(metadata).to.have.own.property('TotalNbPages');
    expect(metadata.TotalNbPages).to.be.a('number');
    expect(metadata).to.have.own.property('PDFFormatVersion');
    expect(metadata.PDFFormatVersion).to.be.a('string');
    expect(metadata.PDFFormatVersion).to.be.equal('1.4');
  });

  it('should get the text from page of pdf file', function (done) {
    const poppl = new Popplonode();
    poppl.load('test/data/test.pdf');
    poppl.getTextFromPage(0, (error, content) => {
      if (error) return done(error);
      expect(content).to.be.a('string');
      done();
    });
  });
});
