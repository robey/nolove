#include <v8.h>
#include <node.h>
#include "context.h"
#include "module.h"

using namespace v8;

NodeProto<NodeLContext, llvm::LLVMContext&> NodeLContext::proto("Context");

void NodeLContext::init() {
  proto.addMethod("newModule", &NodeLContext::newModule);
  proto.addField("msg", String::New("Okay, that worked."));
}

Handle<Value> NodeLContext::newModule(const Arguments& args) {
  if (args.Length() < 1) return throwError("Context#newModule requires one string paramater.");
  return (new NodeLModule(utf8Arg(args, 0), wrapped))->handle_;
}
