#ifndef POPPLONODE_H
#define POPPLONODE_H

#include <cpp/poppler-document.h>
#include <cpp/poppler-global.h>
#include <cpp/poppler-page.h>
#include <nan.h>

class Popplonode : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init);
  poppler::document* doc;

private:
  explicit Popplonode(bool debug = false); 
  ~Popplonode();
  static inline Nan::Persistent<v8::Function>& constructor();

  static NAN_METHOD(New);
  static NAN_METHOD(load);
  static NAN_METHOD(getMetadata);
  static NAN_METHOD(getTextFromPage);

  static NAN_GETTER(getDebug);
  static NAN_SETTER(setDebug);
  
  bool _debug;
};

#endif