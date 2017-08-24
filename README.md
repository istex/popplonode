[![Build Status](https://travis-ci.org/istex/popplonode.svg?branch=master)](https://travis-ci.org/istex/popplonode)

# popplonode
Just a node module for poppler library

## Requirements
This version has been tested only on Ubuntu 16.04 and 14.04

**Debian/Ubuntu**
```shell
sudo apt-get install cmake g++libpoppler-cpp-dev
```

## Install
```shell
npm install git+https://github.com/istex/popplonode.git[#<commit-ish> | #semver:<semver>]
```

## Usage
```javascript
const Popplonode = require('popplonode');

// We load the PDF file into poppl
poppl.load('path/to/my/file.pdf'); 

// We can access the metadata of the PDF file
const metadata = poppl.getMetadata(); // 

poppl.getTextFromPage(0, (error, content) => {
  // do something with the content page
});
```