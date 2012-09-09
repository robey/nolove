#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "nodeproto.h"

using namespace v8;

class NodeLContext : node::ObjectWrap {
private:
  llvm::LLVMContext& llvmContext;
  int id;

  static NodeProto<NodeLContext> proto;

public:
  NodeLContext(llvm::LLVMContext& c) : llvmContext(c), id(23) { }

  static void init();
  static Handle<Value> create(llvm::LLVMContext& c);
  Handle<Value> newModule(const Arguments& args);
};
