#include <v8.h>
#include <node.h>
#include "function.h"
#include "globals.h"

using namespace v8;

// ----- LFunction

NodeProto<LFunction> LFunction::proto("Function");

void LFunction::init() {
  proto.inherit(LValue::proto);
  proto.addMethod("arguments", &LFunction::arguments);
}

Handle<Value>
LFunction::arguments(const Arguments& args) {
  HandleScope scope;
  Local<Array> rv = Array::New(function()->arg_size());
  int index = 0;
  for (llvm::Function::arg_iterator iter = function()->arg_begin(); iter != function()->arg_end(); ++iter, ++index) {
    Handle<Value> item = LArgument::create(&*iter)->handle_;
    rv->Set(Number::New(index), item);
  }
  return scope.Close(rv);
}

// ----- LArgument

NodeProto<LArgument> LArgument::proto("Argument");

void LArgument::init() {
  proto.inherit(LValue::proto);
}
