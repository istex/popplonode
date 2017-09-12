[![Build Status](https://travis-ci.org/istex/popplonode.svg?branch=master)](https://travis-ci.org/istex/popplonode)

# popplonode
Just a node module for poppler library

## Requirements
This version has been tested only on Ubuntu 16.04 and 14.04

**Debian/Ubuntu**
```shell
sudo apt-get install cmake g++ libpoppler-cpp-dev
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