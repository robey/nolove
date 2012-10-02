#include <v8.h>
#include <node.h>
#include "nativecallable.h"

using namespace v8;

NodeProto<NativeCallable> NativeCallable::proto("NativeCallable");

void NativeCallable::init() {
  proto.addMethod("call_d2d", &NativeCallable::call_d2d);
}

// call(...)
Handle<Value> NativeCallable::call_d2d(const Arguments& args) {
  CHECK_ARG_COUNT("call_d2d", 1, 1, "n: Number");
  CHECK_ARG_NUMBER(0);
  typedef double (*fptr)(double);
  fptr fp = (fptr)(handle_->GetPointerFromInternalField(1));
  double rv = (*fp)(args[0]->ToNumber()->Value());
  return Number::New(rv);
}
