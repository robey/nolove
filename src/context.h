#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "nodeproto.h"

using namespace v8;

class LContext : public NodeWrapped {
public:
  static NodeProto<LContext> proto;

  static void init();

  static LContext *create(llvm::LLVMContext* c) {
    return createWrapped<LContext>(c);
  }

  llvm::LLVMContext *context() { return wrapped<llvm::LLVMContext>(); }

  Handle<Value> newModule(const Arguments& args);
  Handle<Value> newIRBuilder(const Arguments& args);
  Handle<Value> newBasicBlock(const Arguments& args);

  // constants
  Handle<Value> getFP(const Arguments& args);
  
  // types
  Handle<Value> getDoubleType(const Arguments& args);
};
