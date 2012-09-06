#pragma once

#include <v8.h>
#include <node.h>

using namespace v8;

class NodeLLVM {
public:
  static void init(Handle<Object> target);
  static Handle<Value> getGlobalContext(const Arguments& args);
};
