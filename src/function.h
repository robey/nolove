#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/DerivedTypes.h"
#include "llvm/Function.h"
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LFunction : public LValue<LFunction, llvm::Function> {
public:
  static NodeProto<LFunction, llvm::Function *> proto;

  LFunction(llvm::FunctionType *type, llvm::Function::LinkageTypes linkage, const char *name, llvm::Module *module) :
    LValue(llvm::Function::Create(type, linkage, name, module)) { }

  static void init();

  Handle<Value> arguments(const Arguments& args);
};

class LArgument : public LValue<LArgument, llvm::Argument> {
public:
  static NodeProto<LArgument, llvm::Argument *> proto;

  LArgument(llvm::Argument *arg) : LValue(arg) { }

  static void init();
};
