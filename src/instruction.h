#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/Instruction.h"
#include "llvm/Instructions.h"
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LInstruction : public LValue {
public:
  static NodeProto<LInstruction> proto;

  static void init();

  static LInstruction *create(llvm::Instruction *x) {
    return createWrapped<LInstruction>(x);
  }

  llvm::Instruction *instruction() { return wrapped<llvm::Instruction>(); }
};

class LReturnInstruction : public LInstruction {
public:
  static NodeProto<LReturnInstruction> proto;

  static void init();

  static LReturnInstruction *create(llvm::ReturnInst *x) {
    return createWrapped<LReturnInstruction>(x);
  }

  llvm::ReturnInst *returnInstruction() { return wrapped<llvm::ReturnInst>(); }
};
