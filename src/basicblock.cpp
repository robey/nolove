#include "basicblock.h"

using namespace v8;

NodeProto<LBasicBlock> LBasicBlock::proto("BasicBlock");

void LBasicBlock::init() {
  proto.inherit(LValue::proto);
//  proto.addMethod("isNullValue", &LConstant::isNullValue);
}
