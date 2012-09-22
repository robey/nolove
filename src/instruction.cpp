#include <v8.h>
#include <node.h>
#include "instruction.h"

using namespace v8;

// ----- LInstruction

NodeProto<LInstruction> LInstruction::proto("Instruction");

void LInstruction::init() {
  proto.inherit(LValue::proto);
//  proto.addMethod("createFMul", &LIRBuilder::createFMul);
}

// ----- LReturnInstruction

NodeProto<LReturnInstruction> LReturnInstruction::proto("ReturnInstruction");

void LReturnInstruction::init() {
  proto.inherit(LInstruction::proto);
//  proto.addMethod("createFMul", &LIRBuilder::createFMul);
}
