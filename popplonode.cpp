#include "popplonode.h"
#include "getTextFromPageAsync.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

using namespace std;
using namespace v8;

Popplonode::Popplonode() {}
Popplonode::~Popplonode() {}

Nan::Persistent<v8::Function>& Popplonode::constructor() {
  static Nan::Persistent<v8::Function> my_constructor;
  return my_constructor;
}

void Popplonode::Init(v8::Local<v8::Object> exports) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Popplonode").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "load", load);
  Nan::SetPrototypeMethod(tpl, "getMetadata", getMetadata);
  Nan::SetPrototypeMethod(tpl, "getTextFromPage", getTextFromPage);

  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  exports->Set(Nan::New("Popplonode").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

void Popplonode::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    Popplonode* obj = new Popplonode();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = {info[0]};
    v8::Local<v8::Function> cons = Nan::New(constructor());
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void Popplonode::load(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 1)
    return Nan::ThrowTypeError("Load requires at least 1 argument");
  Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
  String::Utf8Value val(info[0]->ToString());
  string filename(*val);
  popplonode->doc = poppler::document::load_from_file(filename);
  if (popplonode->doc == nullptr) {
    info.GetReturnValue().Set(Nan::False());
  } else {
    info.GetReturnValue().Set(Nan::True());
  }
}

void Popplonode::getMetadata(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
  Local<Object> metadata = Nan::New<Object>();
  vector<string> infoKeys{popplonode->doc->info_keys()};
  for_each(infoKeys.begin(), infoKeys.end(), [&](string infoKey) {
    Local<String> infoProp = Nan::New<String>(infoKey).ToLocalChecked();
    Local<String> infoValue =
        Nan::New<String>(popplonode->doc->info_key(infoKey).to_latin1().c_str()).ToLocalChecked();
    metadata->Set(infoProp, infoValue);
  });
  info.GetReturnValue().Set(metadata);
}

void Popplonode::getTextFromPage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.Length() < 2)
    return Nan::ThrowTypeError("Load requires at least 2 argument");
  double pageNumber = info[0]->NumberValue();
  Nan::Callback* callback = new Nan::Callback(info[1].As<Function>());
  Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
  Nan::AsyncQueueWorker(new GetTextFromPageAsync(callback, popplonode, pageNumber));
}

NODE_MODULE(popplonode, Popplonode::Init);
