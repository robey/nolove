#pragma once

#include <unistd.h>
#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "llvm/Module.h"
#include "nodeproto.h"

using namespace v8;

class NodeLModule : public NodeWrapped<NodeLModule, llvm::Module *> {
public:
  static NodeProto<NodeLModule, llvm::Module *> proto;

  NodeLModule(const char *name, llvm::LLVMContext &c) : NodeWrapped(new llvm::Module(name, c)) { }
  virtual ~NodeLModule() { delete wrapped; }

  static void init();

  Handle<Value> getModuleIdentifier(const Arguments& args);
  Handle<Value> getDataLayout(const Arguments& args);
  Handle<Value> getTargetTriple(const Arguments& args);

  Handle<Value> dump(const Arguments& args);
};
