#include <v8.h>
#include <node.h>
#include "llvm.h"

using namespace v8;

namespace NodeLLVM {
  void LLVM::init(Handle<Object> target) {
    HandleScope scope;

    Handle<FunctionTemplate> f = FunctionTemplate::New(getContext);
    target->Set(String::NewSymbol("getContext"), f->GetFunction());
  }

  Handle<Value> LLVM::getContext(const Arguments& args) {
    HandleScope scope;

    Local<String> rv = String::New("Hello Robey!");
    return scope.Close(rv);
  }
}

extern "C" {
  static void init(Handle<Object> target) {
    NodeLLVM::LLVM::init(target);
  }

  NODE_MODULE(llvm, init);
}
