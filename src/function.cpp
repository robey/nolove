#include <v8.h>
#include <node.h>
#include "function.h"
#include "globals.h"

using namespace v8;

// ----- LFunction

NodeProto<LFunction, llvm::Function *> LFunction::proto("Function");

void LFunction::init() {
  LValue::init(proto);
  proto.addMethod("arguments", &LFunction::arguments);
}

Handle<Value>
LFunction::arguments(const Arguments& args) {
  HandleScope scope;
  Local<Array> rv = Array::New(wrapped->arg_size());
  int index = 0;
  for (llvm::Function::arg_iterator iter = wrapped->arg_begin(); iter != wrapped->arg_end(); ++iter, ++index) {
    Handle<Value> item = (new LArgument(&*iter))->handle_;
    rv->Set(Number::New(index), item);
  }
  return scope.Close(rv);
}

// ----- LArgument

NodeProto<LArgument, llvm::Argument *> LArgument::proto("Argument");

void LArgument::init() {
  LValue::init(proto);
}
