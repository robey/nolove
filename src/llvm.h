#pragma once

#include <v8.h>
#include <node.h>

using namespace v8;

namespace NodeLLVM {
  class LLVM {
  public:
    static void init(Handle<Object> target);
    static Handle<Value> getContext(const Arguments& args);
  };
}
