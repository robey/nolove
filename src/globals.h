#pragma once

#include "llvm/GlobalValue.h"
#include "nodeproto.h"

using namespace v8;

class LLinkage : public NodeHelper {
public:
  template <typename T, typename Wrapped>
  static void init(NodeProto<T, Wrapped> proto);
};
