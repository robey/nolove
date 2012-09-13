#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "nodeproto.h"

using namespace v8;

class NodeLContext : public NodeWrapped<NodeLContext, llvm::LLVMContext&> {
protected:
  int id;

public:
  static NodeProto<NodeLContext, llvm::LLVMContext&> proto;

  NodeLContext(llvm::LLVMContext& c) : NodeWrapped(c), id(23) { }

  static void init();
  Handle<Value> newModule(const Arguments& args);
  Handle<Value> newBasicBlock(const Arguments& args);

  // types
  Handle<Value> getDoubleType(const Arguments& args);
};
