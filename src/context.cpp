#include "basicblock.h"
#include "constant.h"
#include "context.h"
#include "function.h"
#include "irbuilder.h"
#include "module.h"
#include "type.h"

using namespace v8;

NodeProto<LContext> LContext::proto("Context");

void LContext::init() {
  proto.addMethod("newModule", &LContext::newModule);
  proto.addMethod("newIRBuilder", &LContext::newIRBuilder);
  proto.addMethod("newBasicBlock", &LContext::newBasicBlock);
  proto.addMethod("getFP", &LContext::getFP);
  proto.addMethod("getDoubleType", &LContext::getDoubleType);
}

// newModule(name: String)
Handle<Value> LContext::newModule(const Arguments& args) {
  CHECK_ARG_COUNT("newModule", 1, 1, "name: String");
  return LModule::create(utf8Arg(args, 0), context())->handle_;
}

// newIRBuilder()
Handle<Value> LContext::newIRBuilder(const Arguments& args) {
  return LIRBuilder::create(context())->handle_;
}

// newBasicBlock(name: String, parent: Function, optional insertBefore: BasicBlock)
Handle<Value> LContext::newBasicBlock(const Arguments& args) {
  CHECK_ARG_COUNT("newBasicBlock", 2, 3, "name: String, parent: Function, optional insertBefore: BasicBlock");
  CHECK_ARG_TYPE(LFunction, 1);
  LFunction *parent = LFunction::proto.unwrap(args[1]);
  if (args.Length() > 2) {
    CHECK_ARG_TYPE(LBasicBlock, 2);
    LBasicBlock *insertBefore = LBasicBlock::proto.unwrap(args[2]);
    return LBasicBlock::create(context(), utf8Arg(args, 0), parent->function(), insertBefore->block())->handle_;
  } else {
    return LBasicBlock::create(context(), utf8Arg(args, 0), parent->function())->handle_;
  }
}

// getFP(value: Number)
Handle<Value> LContext::getFP(const Arguments& args) {
  CHECK_ARG_COUNT("getFP", 1, 1, "value: Number");
  CHECK_ARG_NUMBER(0);
  double value = args[0]->ToNumber()->Value();
  return LConstantFP::create(context(), llvm::APFloat(value))->handle_;
}

// getDoubleType()
Handle<Value> LContext::getDoubleType(const Arguments& args) {
  return LType::create(llvm::Type::getDoubleTy(*context()))->handle_;
}

