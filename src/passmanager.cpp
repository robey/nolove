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
  proto.inherit(LPass::proto);
  proto.addMethod("toString", &LTargetData::toString);
}

Handle<Value> LTargetData::toString(const Arguments& args) {
  return String::New(targetData()->getStringRepresentation().c_str());
}

// ----- LFunctionPassManager

NodeProto<LFunctionPassManager> LFunctionPassManager::proto("FunctionPassManager");

void LFunctionPassManager::init() {
  proto.addMethod("add", &LFunctionPassManager::add);
  proto.addMethod("doInitialization", &LFunctionPassManager::doInitialization);
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

// doInitialization()
Handle<Value>
LFunctionPassManager::doInitialization(const Arguments& args) {
  return Boolean::New(functionPassManager()->doInitialization());
}
