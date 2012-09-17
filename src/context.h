#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "nodeproto.h"

using namespace v8;

class LContext : public NodeWrapped<LContext, llvm::LLVMContext&> {
protected:
  int id;

public:
  static NodeProto<LContext, llvm::LLVMContext&> proto;

  LContext(llvm::LLVMContext& c) : NodeWrapped(c), id(23) { }

  static void init();
  Handle<Value> newModule(const Arguments& args);
  Handle<Value> newBasicBlock(const Arguments& args);

  // types
  Handle<Value> getDoubleType(const Arguments& args);
};