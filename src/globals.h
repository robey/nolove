#pragma once

#include "llvm/GlobalValue.h"
#include "nodeproto.h"

using namespace v8;

class LLinkage : public NodeHelper {
public:
  static void init(Handle<Object> proto);
};
