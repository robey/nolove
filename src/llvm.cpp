#include <v8.h>
#include <node.h>
#include "llvm.h"
#include "context.h"
#include "llvm/LLVMContext.h"

using namespace v8;

void NodeLLVM::init(Handle<Object> target) {
  HandleScope scope;

  Handle<FunctionTemplate> f = FunctionTemplate::New(getGlobalContext);
  target->Set(String::NewSymbol("getGlobalContext"), f->GetFunction());
}

Handle<Value> NodeLLVM::getGlobalContext(const Arguments& args) {
  NodeLContext *c = new NodeLContext(llvm::getGlobalContext());
  return c->handle_;
}

extern "C" {
  static void init(Handle<Object> target) {
    NodeLLVM::init(target);
    NodeLContext::init();
  }

  NODE_MODULE(llvm, init);
}
