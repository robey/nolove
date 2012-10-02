#include <v8.h>
#include <node.h>
#include "executionengine.h"
#include "function.h"
#include "passmanager.h"

using namespace v8;

NodeProto<LExecutionEngine> LExecutionEngine::proto("ExecutionEngine");

void LExecutionEngine::init() {
  proto.addMethod("getPointerToFunction", &LExecutionEngine::getPointerToFunction);
  proto.addMethod("getTargetData", &LExecutionEngine::getTargetData);
}

// getPointerToFunction(function: Function)
Handle<Value>
LExecutionEngine::getPointerToFunction(const Arguments& args) {
  CHECK_ARG_COUNT("getPointerToFunction", 1, 1, "function: Function");
  CHECK_ARG_TYPE(LFunction, 0);
  LFunction *function = LFunction::proto.unwrap(args[0]);
  executionEngine()->getPointerToFunction(function->function());
  return Undefined();
}

// getTargetData()
Handle<Value>
LExecutionEngine::getTargetData(const Arguments& args) {
  return LTargetData::create(new llvm::TargetData(*executionEngine()->getTargetData()))->handle_;
}
