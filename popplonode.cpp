#include "popplonode.h"
#include "getTextFromPageAsync.h"
#include <algorithm>
#include <iostream>
#include <memory>
#include <string>

using namespace std;
using namespace v8;

Popplonode::Popplonode(bool debug) : _debug(debug) {
  poppler::set_debug_error_function([](const std::string& msg, void*) { return; }, nullptr);
}
Popplonode::~Popplonode() {}

Nan::Persistent<v8::Function>& Popplonode::constructor() {
  static Nan::Persistent<v8::Function> my_constructor;
  return my_constructor;
}

NAN_MODULE_INIT(Popplonode::Init) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(Popplonode::New);
  tpl->SetClassName(Nan::New("Popplonode").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "load", load);
  Nan::SetPrototypeMethod(tpl, "getMetadata", getMetadata);
  Nan::SetPrototypeMethod(tpl, "getTextFromPage", getTextFromPage);

  Local<ObjectTemplate> instTpl = tpl->InstanceTemplate();
  Nan::SetAccessor(instTpl, Nan::New<v8::String>("debug").ToLocalChecked(), Popplonode::getDebug,
                   Popplonode::setDebug);

  constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("Popplonode").ToLocalChecked(), tpl->GetFunction());
}

NAN_METHOD(Popplonode::New) {
  if (info.IsConstructCall()) {
    Popplonode* obj = new Popplonode();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    const int argc = 1;
    Local<Value> argv[argc] = {info[0]};
    Local<Function> cons = Nan::New(constructor());
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}
NAN_METHOD(Popplonode::load) {
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

NAN_METHOD(Popplonode::getMetadata) {
  Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
  Local<Object> metadata = Nan::New<Object>();
  vector<string> infoKeys{popplonode->doc->info_keys()};
  for_each(infoKeys.begin(), infoKeys.end(), [&](string infoKey) {
    Local<String> infoProp = Nan::New<String>(infoKey).ToLocalChecked();
    Local<String> infoValue =
        Nan::New<String>(popplonode->doc->info_key(infoKey).to_latin1().c_str()).ToLocalChecked();
    metadata->Set(infoProp, infoValue);
  });
  Local<String> nbPageProp = Nan::New<String>("TotalNbPages").ToLocalChecked();
  Local<Number> nbPageValue = Nan::New<Number>(popplonode->doc->pages());
  Local<String> numVersionProp = Nan::New<String>("PDFFormatVersion").ToLocalChecked();
  int major = 0, minor = 0;
  popplonode->doc->get_pdf_version(&major, &minor);
  string pdfVersion = std::to_string(major) + "." + std::to_string(minor);
  Local<String> numVersionValue = Nan::New<String>(pdfVersion).ToLocalChecked();
  metadata->Set(nbPageProp, nbPageValue);
  metadata->Set(numVersionProp, numVersionValue);
  metadata->Set(nbPageProp, nbPageValue);
  info.GetReturnValue().Set(metadata);
}

NAN_METHOD(Popplonode::getTextFromPage) {
  if (info.Length() < 2)
    return Nan::ThrowTypeError("Load requires at least 2 argument");
  double pageNumber = info[0]->NumberValue();
  Nan::Callback* callback = new Nan::Callback(info[1].As<Function>());
  Popplonode* popplonode = Nan::ObjectWrap::Unwrap<Popplonode>(info.Holder());
  Nan::AsyncQueueWorker(new GetTextFromPageAsync(callback, popplonode, pageNumber));
}

NAN_GETTER(Popplonode::getDebug) {
  Isolate* isolate = info.GetIsolate();
  Popplonode* obj = ObjectWrap::Unwrap<Popplonode>(info.This());
  info.GetReturnValue().Set(v8::Boolean::New(isolate, obj->_debug));
}

NAN_SETTER(Popplonode::setDebug) {
  Popplonode* obj = ObjectWrap::Unwrap<Popplonode>(info.This());
  bool input = value->BooleanValue();
  if (input) {
    poppler::set_debug_error_function([](const std::string& msg, void*) { 
      std::cerr << "poppler/" << msg << std::endl;
    }, nullptr);
  } else {
    poppler::set_debug_error_function([](const std::string& msg, void*) { return; }, nullptr);
  }
  obj->_debug = value->BooleanValue();
}

void InitPopplonode(v8::Local<v8::Object> exports) { Popplonode::Init(exports); }

NODE_MODULE(popplonode, InitPopplonode);
