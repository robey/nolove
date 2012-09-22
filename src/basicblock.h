#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/BasicBlock.h"
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LBasicBlock : public LValue {
public:
  static NodeProto<LBasicBlock> proto;

  static void init();

  static LBasicBlock *create(llvm::LLVMContext *c, const char *name, llvm::Function *parent = NULL, llvm::BasicBlock *insertBefore = NULL) {
    return createWrapped<LBasicBlock>(llvm::BasicBlock::Create(*c, name, parent, insertBefore));
  }

  llvm::BasicBlock *block() { return wrapped<llvm::BasicBlock>(); }

//  Handle<Value> isDoubleType(const Arguments& args);
};
