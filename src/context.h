#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"

using namespace v8;

class NodeLContext : node::ObjectWrap {
private:
  llvm::LLVMContext& llvmContext;

  static Persistent<FunctionTemplate> prototypeObject;

public:
  NodeLContext(llvm::LLVMContext& c) : llvmContext(c) { }

  static void init();
  static Handle<Value> create(llvm::LLVMContext& c);
  static Handle<Value> newModule(const Arguments& args);
};
