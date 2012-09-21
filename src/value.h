#pragma once

#include <sstream>
#include <v8.h>
#include <node.h>
#include "llvm/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "nodeproto.h"
#include "type.h"

using namespace v8;

/**
 * In LLVM, almost everything descends from this interface.
 */
class LValue : public NodeWrapped {
public:
  static NodeProto<LValue> proto;

  static void init();

  static LValue *create(llvm::Value *v) {
    return createWrapped<LValue>(v);
  }

  llvm::Value *value() { return wrapped<llvm::Value>(); }

  Handle<Value> getType(const Arguments& args);
  Handle<Value> hasName(const Arguments& args);
  Handle<Value> getName(const Arguments& args);
  Handle<Value> setName(const Arguments& args);
  Handle<Value> toString(const Arguments& args);
};
