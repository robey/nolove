#include <v8.h>
#include <node.h>
#include "basicblock.h"
#include "instruction.h"
#include "irbuilder.h"
#include "value.h"

using namespace v8;

NodeProto<LIRBuilder> LIRBuilder::proto("IRBuilder");

void LIRBuilder::init() {
  proto.addMethod("setInsertPoint", &LIRBuilder::setInsertPoint);
  proto.addMethod("createFMul", &LIRBuilder::createFMul);
  proto.addMethod("createRet", &LIRBuilder::createRet);
  proto.addMethod("createRetVoid", &LIRBuilder::createRetVoid);
}

Handle<Value> LIRBuilder::setInsertPoint(const Arguments& args) {
  CHECK_ARG_COUNT("setInsertPoint", 1, 1, "block: BasicBlock");
  CHECK_ARG_TYPE(LBasicBlock, 0);
  irBuilder()->SetInsertPoint(LBasicBlock::proto.unwrap(args[0])->block());
  return Undefined();
}

Handle<Value> LIRBuilder::createFMul(const Arguments& args) {
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

Handle<Value> LIRBuilder::createRet(const Arguments& args) {
  CHECK_ARG_COUNT("createRet", 1, 1, "value: Value");
  CHECK_ARG_TYPE(LValue, 0);
  LValue *value = LValue::proto.unwrap(args[0]);
  return LReturnInstruction::create(irBuilder()->CreateRet(value->value()))->handle_;
}

Handle<Value> LIRBuilder::createRetVoid(const Arguments& args) {
  return LReturnInstruction::create(irBuilder()->CreateRetVoid())->handle_;
}
