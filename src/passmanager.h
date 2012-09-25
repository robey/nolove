#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/Pass.h"
#include "llvm/PassManager.h"
#include "llvm/Target/TargetData.h"
#include "nodeproto.h"

using namespace v8;

class LPass : public NodeWrapped {
public:
  static NodeProto<LPass> proto;

  static void init();

  static LPass *create(llvm::Pass *pass) {
    return createWrapped<LPass>(pass);
  }

  llvm::Pass *pass() { return wrapped<llvm::Pass>(); }
};

class LTargetData : public LPass {
public:
  static NodeProto<LTargetData> proto;

  static void init();

  static LTargetData *create(llvm::TargetData *targetData) {
    return createWrapped<LTargetData>(targetData);
  }

  llvm::TargetData *targetData() { return wrapped<llvm::TargetData>(); }
};

class LFunctionPassManager : public NodeWrapped {
public:
  static NodeProto<LFunctionPassManager> proto;

  static void init();

  static LFunctionPassManager *create(llvm::Module *module) {
    return createWrapped<LFunctionPassManager>(new llvm::FunctionPassManager(module));
  }
  virtual ~LFunctionPassManager() { delete functionPassManager(); }

  llvm::FunctionPassManager *functionPassManager() { return wrapped<llvm::FunctionPassManager>(); }

  Handle<Value> add(const Arguments& args);
};
