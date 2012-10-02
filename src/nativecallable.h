#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "nodeproto.h"

using namespace v8;

/*
 * a native callable function. we'll try to match the type based on the types
 * of javascript parameters, so this is hella dangerous.
 */
class NativeCallable : public NodeWrapped {
public:
  static NodeProto<NativeCallable> proto;

  static void init();

  static NativeCallable *create(void *ptr) {
    return createWrapped<NativeCallable>(ptr);
  }

  Handle<Value> call_d2d(const Arguments& args);
};
