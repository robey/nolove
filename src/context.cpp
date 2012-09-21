#include "context.h"
#include "irbuilder.h"
#include "module.h"
#include "type.h"

using namespace v8;

NodeProto<LContext> LContext::proto("Context");

void LContext::init() {
  proto.addMethod("newModule", &LContext::newModule);
  proto.addMethod("newIRBuilder", &LContext::newIRBuilder);
  proto.addMethod("newBasicBlock", &LContext::newBasicBlock);
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



  return LModule::create(utf8Arg(args, 0), context())->handle_;
}

// getDoubleType()
Handle<Value> LContext::getDoubleType(const Arguments& args) {
  return LType::create(llvm::Type::getDoubleTy(*context()))->handle_;
}
