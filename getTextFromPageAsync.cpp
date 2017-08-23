#include "getTextFromPageAsync.h"

using namespace std;
using namespace v8;

GetTextFromPageAsync::GetTextFromPageAsync(Nan::Callback* callback, Popplonode* popplonode, double pageNumber)
    : Nan::AsyncWorker(callback), popplonode(popplonode), pageNumber(pageNumber) {}
GetTextFromPageAsync::~GetTextFromPageAsync() {}
void GetTextFromPageAsync::Execute() { currentPage = popplonode->doc->create_page(pageNumber); }
// Executes in event loop
void GetTextFromPageAsync::HandleOKCallback() {
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