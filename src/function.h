#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/DerivedTypes.h"
#include "llvm/Function.h"
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LFunction : public LValue {
public:
  static NodeProto<LFunction> proto;

  static void init();

  static LFunction *create(llvm::FunctionType *type, llvm::Function::LinkageTypes linkage, const char *name, llvm::Module *module) {
    return createWrapped<LFunction>(llvm::Function::Create(type, linkage, name, module));
  }

  llvm::Function *function() { return wrapped<llvm::Function>(); }

  Handle<Value> arguments(const Arguments& args);
};

class LArgument : public LValue {
public:
  static NodeProto<LArgument> proto;

  static void init();

  static LArgument *create(llvm::Argument *arg) {
    return createWrapped<LArgument>(arg);
  }

  llvm::Argument *argument() { return wrapped<llvm::Argument>(); }
};
