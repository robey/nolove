#pragma once

#include <unistd.h>
#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "nodeproto.h"
#include "type.h"

using namespace v8;

class LModule : public NodeWrapped {
public:
  static NodeProto<LModule> proto;

  static void init();

  static LModule *create(const char *name, llvm::LLVMContext *c) {
    return createWrapped<LModule>(new llvm::Module(name, *c));
  }

  llvm::Module *module() { return wrapped<llvm::Module>(); }

  virtual ~LModule() { delete module(); }

  Handle<Value> getModuleIdentifier(const Arguments& args);
  Handle<Value> getDataLayout(const Arguments& args);
  Handle<Value> getTargetTriple(const Arguments& args);

  Handle<Value> dump(const Arguments& args);

  Handle<Value> newFunction(const Arguments& args);
  Handle<Value> newExecutionEngine(const Arguments& args);
  Handle<Value> newFunctionPassManager(const Arguments& args);
};
