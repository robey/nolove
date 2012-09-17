#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/DerivedTypes.h"
#include "llvm/Function.h"
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LFunction : public LValue<LFunction, llvm::Function *> {
public:
  static NodeProto<LFunction, llvm::Function *> proto;

  LFunction(llvm::FunctionType *type, llvm::Function::LinkageTypes linkage, const char *name, llvm::Module *module) :
    LValue(llvm::Function::Create(type, linkage, name, module)) { }

  static void init();
};

class LArgument : public NodeWrapped<LArgument, llvm::Argument&> {
public:
  static NodeProto<LArgument, llvm::Argument&> proto;

  LArgument(llvm::Argument& arg) : NodeWrapped(arg) { }

  static void init();
};

/*

  // Set names for all arguments.
  unsigned Idx = 0;
  for (Function::arg_iterator AI = F->arg_begin(); Idx != Args.size();
       ++AI, ++Idx) {
    AI->setName(Args[Idx]);
    
    // Add arguments to variable symbol table.
    NamedValues[Args[Idx]] = AI;
  }
  */
