#pragma once

#include <unistd.h>
#include <sstream>
#include <v8.h>
#include <node.h>
#include "llvm/DerivedTypes.h"
#include "llvm/Function.h"
#include "nodeproto.h"

using namespace v8;

class LType : public NodeWrapped {
public:
  static NodeProto<LType> proto;

  static void init();

  static LType *create(const llvm::Type *type) {
    return createWrapped<LType>(const_cast<llvm::Type *>(type));
  }

  llvm::Type *type() { return wrapped<llvm::Type>(); }

  Handle<Value> isDoubleType(const Arguments& args);
  Handle<Value> isFunctionType(const Arguments& args);
  Handle<Value> toString(const Arguments& args);
};

class LFunctionType : public LType {
public:
  static NodeProto<LFunctionType> proto;

  static void init();

  static LFunctionType *create(const llvm::Type *result, const std::vector<const llvm::Type *>& params, bool isVarArg) {
    return createWrapped<LFunctionType>(llvm::FunctionType::get(result, params, isVarArg));
  }

  static LFunctionType *create(const llvm::Type *result, bool isVarArg) {
    return createWrapped<LFunctionType>(llvm::FunctionType::get(result, isVarArg));
  }

  llvm::FunctionType *functionType() { return wrapped<llvm::FunctionType>(); }

  Handle<Value> isVarArg(const Arguments& args);
  Handle<Value> getNumParams(const Arguments& args);
  Handle<Value> getParamType(const Arguments& args);
};
