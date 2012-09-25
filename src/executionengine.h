#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "nodeproto.h"

using namespace v8;

class LExecutionEngine : public NodeWrapped {
public:
  static NodeProto<LExecutionEngine> proto;

  static void init();

  static LExecutionEngine *create(llvm::Module *module) {
    return createWrapped<LExecutionEngine>(llvm::ExecutionEngine::create(module));
  }

  llvm::ExecutionEngine *executionEngine() { return wrapped<llvm::ExecutionEngine>(); }

  Handle<Value> getPointerToFunction(const Arguments& args);
  Handle<Value> getTargetData(const Arguments& args);
};
