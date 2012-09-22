#include <v8.h>
#include <node.h>
#include "irbuilder.h"

using namespace v8;

NodeProto<LIRBuilder> LIRBuilder::proto("IRBuilder");

void LIRBuilder::init() {
  proto.addMethod("createFMul", &LIRBuilder::createFMul);
}

Handle<Value>
LIRBuilder::createFMul(const Arguments& args) {
  CHECK_ARG_COUNT("createFMul", 2, 3, "left: Value, right: Value, optional name: String");
  CHECK_ARG_TYPE(LValue, 0);
  CHECK_ARG_TYPE(LValue, 1);
  LValue *left = LValue::proto.unwrap(args[0]);
  LValue *right = LValue::proto.unwrap(args[1]);
  if (args.Length() > 2) {
    return LValue::create(irBuilder()->CreateFMul(left->value(), right->value(), utf8Arg(args, 2)))->handle_;
  } else {
    return LValue::create(irBuilder()->CreateFMul(left->value(), right->value()))->handle_;
  }
  return Undefined();
}
