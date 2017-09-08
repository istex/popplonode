#ifndef POPPLONODE_H
#define POPPLONODE_H

#include <nan.h>
#include <cpp/poppler-document.h>
#include <cpp/poppler-page.h>

class Popplonode : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  poppler::document* doc;

private:
  explicit Popplonode(); 
  ~Popplonode();
  static NAN_METHOD(New);
  static NAN_METHOD(load);
  static NAN_METHOD(getMetadata);
  static NAN_METHOD(getTextFromPage);
  static inline Nan::Persistent<v8::Function>& constructor();
};

#endif