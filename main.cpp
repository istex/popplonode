#include <algorithm>
#include <cpp/poppler-document.h>
#include <cpp/poppler-page.h>
#include <memory>
#include <nan.h>
#include <string>
#include <iostream>

using namespace std;
using namespace v8;

class Popplonode : public Nan::ObjectWrap {
public:
  static NAN_MODULE_INIT(Init) {
    Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Popplonode").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "load", load);
    Nan::SetPrototypeMethod(tpl, "getMetadata", getMetadata);
    Nan::SetPrototypeMethod(tpl, "getTextFromPage", getTextFromPage);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Popplonode").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
  }

private:
  explicit Popplonode() {}
  ~Popplonode() {}

  static NAN_METHOD(New) {
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

  static NAN_METHOD(load) {
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

  static NAN_METHOD(getMetadata) {
    Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
    Local<Object> metadata = Nan::New<Object>();
    vector<string> infoKeys{popplonode->doc->info_keys()};
    for_each(infoKeys.begin(), infoKeys.end(), [&](string infoKey) {
      Local<String> infoProp = Nan::New<String>(infoKey).ToLocalChecked();
      Local<String> infoValue = Nan::New<String>(popplonode->doc->info_key(infoKey).to_latin1().c_str()).ToLocalChecked();
      metadata->Set(infoProp, infoValue);
    });
    info.GetReturnValue().Set(metadata);
  }

  static NAN_METHOD(getTextFromPage) {
    if (info.Length() < 2)
      return Nan::ThrowTypeError("Load requires at least 2 argument");
    double pageNumber = info[0]->NumberValue();
    Nan::Callback *callback = new Nan::Callback(info[1].As<Function>());
    Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
    poppler::page* currentPage{popplonode->doc->create_page(pageNumber)};
    if (currentPage != nullptr) {
      auto byteArrayResult = currentPage->text().to_utf8();
      string result{byteArrayResult.begin(), byteArrayResult.end()};
      Local<Value> argv[] = {Nan::Null(), Nan::New<String>(result.c_str()).ToLocalChecked()};
      callback->Call(2, argv);
    } else {
      Local<Value> argv[] = {Nan::Error("Page corrupted")};
      callback->Call(1, argv);
    }
  }

  static inline Nan::Persistent<v8::Function>& constructor() {
    static Nan::Persistent<v8::Function> my_constructor;
    return my_constructor;
  }

  poppler::document* doc;
};

NODE_MODULE(popplernodetest, Popplonode::Init);
