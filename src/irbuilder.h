#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/Support/IRBuilder.h"
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LIRBuilder : public NodeWrapped {
public:
  static NodeProto<LIRBuilder> proto;

  static void init();

  static LIRBuilder *create(llvm::LLVMContext *c) {
    return createWrapped<LIRBuilder>(new llvm::IRBuilder<>(*c));
  }

  llvm::IRBuilder<> *irBuilder() { return wrapped<llvm::IRBuilder<> >(); }

  Handle<Value> createFMul(const Arguments& args);
};
