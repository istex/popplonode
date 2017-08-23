#ifndef POPPLONODE_H
#define POPPLONODE_H

#include <nan.h>
#include <cpp/poppler-document.h>
#include <cpp/poppler-page.h>

class Popplonode : public Nan::ObjectWrap {
public:
  static void Init(v8::Local<v8::Object> exports);
  poppler::document* doc;

private:
  explicit Popplonode(); 
  ~Popplonode();
  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void load(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void getMetadata(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void getTextFromPage(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static inline Nan::Persistent<v8::Function>& constructor();
};

#endif