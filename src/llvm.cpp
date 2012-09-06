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
  return NodeLContext::create(llvm::getGlobalContext());
}

extern "C" {
  static void init(Handle<Object> target) {
    NodeLLVM::init(target);
    NodeLContext::init();
  }

  NODE_MODULE(llvm, init);
}
