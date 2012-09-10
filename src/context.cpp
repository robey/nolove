#include <v8.h>
#include <node.h>
#include "context.h"

using namespace v8;

NodeProto<NodeLContext, llvm::LLVMContext&> NodeLContext::proto("LLVMContext");

void NodeLContext::init() {
  HandleScope scope;

  proto.addMethod("newModule", &NodeLContext::newModule);
  proto.addField("msg", String::New("Okay, that worked."));
}

Handle<Value> NodeLContext::newModule(const Arguments& args) {
  HandleScope scope;
  printf("id=%d\n", id);
  Local<String> rv = String::New("hello from crazy town part 2!");
  return scope.Close(rv);
}
