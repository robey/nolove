#include "context.h"
#include "module.h"
#include "type.h"

using namespace v8;

NodeProto<NodeLContext, llvm::LLVMContext&> NodeLContext::proto("Context");

void NodeLContext::init() {
  proto.addMethod("newModule", &NodeLContext::newModule);
  proto.addMethod("newBasicBlock", &NodeLContext::newBasicBlock);
  proto.addMethod("getDoubleType", &NodeLContext::getDoubleType);
}

// newModule(name: String)
Handle<Value> NodeLContext::newModule(const Arguments& args) {
  if (args.Length() < 1) return throwError("Context#newModule requires one string paramater.");
  return (new NodeLModule(utf8Arg(args, 0), wrapped))->handle_;
}

// newBasicBlock(name: String, parent: Function, optional insertBefore: BasicBlock)
Handle<Value> NodeLContext::newBasicBlock(const Arguments& args) {
  if (args.Length() < 1) return throwError("Context#newModule requires one string paramater.");
  return (new NodeLModule(utf8Arg(args, 0), wrapped))->handle_;
}

// getDoubleType()
Handle<Value> NodeLContext::getDoubleType(const Arguments& args) {
  return (new LType(llvm::Type::getDoubleTy(wrapped)))->handle_;
}
