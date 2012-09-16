#include "context.h"
#include "module.h"
#include "type.h"

using namespace v8;

NodeProto<LContext, llvm::LLVMContext&> LContext::proto("Context");

void LContext::init() {
  proto.addMethod("newModule", &LContext::newModule);
  proto.addMethod("newBasicBlock", &LContext::newBasicBlock);
  proto.addMethod("getDoubleType", &LContext::getDoubleType);
}

// newModule(name: String)
Handle<Value> LContext::newModule(const Arguments& args) {
  CHECK_ARG_COUNT("newModule", 1, 1, "name: String");
  return (new NodeLModule(utf8Arg(args, 0), wrapped))->handle_;
}

// newBasicBlock(name: String, parent: Function, optional insertBefore: BasicBlock)
Handle<Value> LContext::newBasicBlock(const Arguments& args) {
  CHECK_ARG_COUNT("newBasicBlock", 2, 3, "name: String, parent: Function, optional insertBefore: BasicBlock");



  return (new NodeLModule(utf8Arg(args, 0), wrapped))->handle_;
}

// getDoubleType()
Handle<Value> LContext::getDoubleType(const Arguments& args) {
  return (new LType(llvm::Type::getDoubleTy(wrapped)))->handle_;
}
