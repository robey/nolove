#pragma once

#include <unistd.h>
#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "nodeproto.h"
#include "type.h"

using namespace v8;

class LModule : public NodeWrapped<LModule, llvm::Module *> {
public:
  static NodeProto<LModule, llvm::Module *> proto;

  LModule(const char *name, llvm::LLVMContext &c) : NodeWrapped(new llvm::Module(name, c)) { }
  //virtual ~LModule() { delete wrapped; }

  static void init();

  Handle<Value> getModuleIdentifier(const Arguments& args);
  Handle<Value> getDataLayout(const Arguments& args);
  Handle<Value> getTargetTriple(const Arguments& args);

  Handle<Value> dump(const Arguments& args);

  Handle<Value> newFunction(const Arguments& args);
};
