[![Build Status](https://travis-ci.org/istex/popplonode.svg?branch=master)](https://travis-ci.org/istex/popplonode)

# popplonode
Get the metadata & text extraction from a PDF file 

# Why Popplonode
Popplonode is an [addons node.js](https://nodejs.org/api/addons.html) which means it use pure c++ code, it's clearly faster than [PDFJS](https://www.npmjs.com/package/pdfjs) & it's faster than a spawn of Poppler pdfinfo too!  because we only use specific functions of it.

## Requirements
This version is working for NodeJs 8.4, 8.5, 6.1 & 4.8 (LTS) on Linux & OSX, a working for windows is in projess..

**(FOR DEV only)**
```shell
sudo apt-get install cmake g++
```

## Install
```shell
npm install git+https://github.com/istex/popplonode.git[#<commit-ish> | #semver:<semver>]
```

## Usage
```javascript
const Popplonode = require('popplonode');

const poppl = new Popplonode();

// We load the PDF file into poppl
poppl.load('path/to/my/file.pdf'); 

// We can access the metadata of the PDF file
const metadata = poppl.getMetadata(); // 

poppl.getTextFromPage(0, (error, content) => {
  // do something with the content page
});
```

## API

### load(string)
arguments: 
- **string** path to your pdf file

### getMetadata()
returns: 
- **object** returns an object that contains all of the pdf's metadata
```js
// example of an metadata object return
{ 
  CreationDate: 'D:20100304130800+01\'00\'',
  Author: 'manshanden',
  Creator: 'PScript5.dll Version 5.2',
  Producer: 'Acrobat Distiller 7.0.5 (Windows)',
  ModDate: 'D:20100304130837+01\'00\'',
  Title: 'Microsoft Word - Test document Word.doc',
  TotalNbPages: 1,
  PDFFormatVersion: '1.4'
}
```

### getTextFromPage(number, function)
arguments : 
- **number** page number (first page start at zero)
- **function** callback who return page text