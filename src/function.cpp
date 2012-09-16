#include <v8.h>
#include <node.h>
#include "function.h"
#include "globals.h"

using namespace v8;

NodeProto<LFunction, llvm::Function *> LFunction::proto("Function");

void LFunction::init() {
  LLinkage::init(proto);
}

NodeProto<LArgument, llvm::Argument&> LArgument::proto("Argument");

void LArgument::init() {
  proto.addMethod("setName", &LArgument::setName);
}

// actually this should be in LValue (oh gawd).
Handle<Value> LArgument::setName(const Arguments& args) {
  CHECK_ARG_COUNT("setName", 1, 1, "name: String");
  String::Utf8Value name(args[0]->ToString());
  wrapped.setName(*name);
  return v8::Undefined();
}
