#pragma once

#include <unistd.h>
#include <v8.h>
#include <node.h>
#include "llvm/DerivedTypes.h"
#include "llvm/Function.h"
#include "nodeproto.h"

using namespace v8;

template <typename T, typename Wrapped>
class LAbstractType : public NodeWrapped<T, Wrapped> {
public:
  static void init(NodeProto<T, Wrapped> proto);

  LAbstractType(Wrapped wrapped) : NodeWrapped<T, Wrapped>(wrapped) { }

  Handle<Value> isDoubleType(const Arguments& args);
};

class LType : public LAbstractType<LType, const llvm::Type *> {
public:
  static NodeProto<LType, const llvm::Type *> proto;

  static void init();

  LType(const llvm::Type *type) : LAbstractType(type) { }
};

class LFunctionType : public LAbstractType<LFunctionType, llvm::FunctionType *> {
public:
  static NodeProto<LFunctionType, llvm::FunctionType *> proto;

  static void init();

  LFunctionType(const llvm::Type *result, const std::vector<const llvm::Type *>& params, bool isVarArg) :
    LAbstractType(llvm::FunctionType::get(result, params, isVarArg)) { }
  LFunctionType(const llvm::Type *result, bool isVarArg) :
    LAbstractType(llvm::FunctionType::get(result, isVarArg)) { }
//  Handle<Value> dump(const Arguments& args);
};
