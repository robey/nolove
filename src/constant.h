#pragma once

#include <v8.h>
#include <node.h>
#include <llvm/ADT/APFloat.h>
#include <llvm/Constants.h>
#include "nodeproto.h"
#include "value.h"

using namespace v8;

class LConstant : public LValue {
public:
  static NodeProto<LConstant> proto;

  static void init();

  static LConstant *create(const llvm::Constant *x) {
    return createWrapped<LConstant>(const_cast<llvm::Constant *>(x));
  }

  llvm::Constant *constant() { return wrapped<llvm::Constant>(); }

  Handle<Value> isNullValue(const Arguments& args);
};

// floating-point constant
class LConstantFP : public LConstant {
public:
  static NodeProto<LConstantFP> proto;

  static void init();

  static LConstantFP *create(llvm::LLVMContext *c, const llvm::APFloat& value) {
    return createWrapped<LConstantFP>(llvm::ConstantFP::get(*c, value));
  }

  llvm::ConstantFP *constantFP() { return wrapped<llvm::ConstantFP>(); }

  Handle<Value> isZero(const Arguments& args);
  // weird: the docs say this exists. it does not.
//  Handle<Value> isNegative(const Arguments& args);
  Handle<Value> isExactlyValue(const Arguments& args);
};
