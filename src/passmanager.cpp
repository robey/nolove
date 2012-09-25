#include <v8.h>
#include <node.h>
#include "passmanager.h"

using namespace v8;

// ----- LPass

NodeProto<LPass> LPass::proto("Pass");

void LPass::init() {
}

// ----- LTargetData

NodeProto<LTargetData> LTargetData::proto("TargetData");

void LTargetData::init() {
}

// ----- LFunctionPassManager

NodeProto<LFunctionPassManager> LFunctionPassManager::proto("FunctionPassManager");

void LFunctionPassManager::init() {
  proto.addMethod("add", &LFunctionPassManager::add);
}

// getPointerToFunction(function: Function)
Handle<Value>
LFunctionPassManager::add(const Arguments& args) {
  CHECK_ARG_COUNT("add", 1, 1, "pass: Pass");
  CHECK_ARG_TYPE(LPass, 0);
  LPass *pass = LPass::proto.unwrap(args[0]);
  functionPassManager()->add(pass->pass());
  return Undefined();
}
