#ifndef GET_TEXT_FROM_PAGE_ASYNC_H
#define GET_TEXT_FROM_PAGE_ASYNC_H

#include <nan.h>
#include "popplonode.h"

class GetTextFromPageAsync : public Nan::AsyncWorker {
public:
  GetTextFromPageAsync(Nan::Callback* callback, Popplonode* popplonode);
  ~GetTextFromPageAsync();
  void Execute();
  void HandleOKCallback();
private: 
  Popplonode* popplonode;
  double pageNumber;
  poppler::page* currentPage;
};

#endif