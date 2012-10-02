#pragma once

#include "nodeproto.h"

using namespace v8;

class NodeLLVM : public NodeHelper {
public:
  static void init(Handle<Object> target);

  static Handle<Value> getGlobalContext(const Arguments& args);
  static Handle<Value> getFunctionType(const Arguments& args);

  // passes
  static Handle<Value> createBasicAliasAnalysisPass(const Arguments& args);

};
