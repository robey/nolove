#include "constant.h"

using namespace v8;

// ----- LConstant

NodeProto<LConstant> LConstant::proto("Constant");

void LConstant::init() {
  proto.inherit(LValue::proto);
  proto.addMethod("isNullValue", &LConstant::isNullValue);
}

// isNullValue()
Handle<Value> LConstant::isNullValue(const Arguments& args) {
  return Boolean::New(constant()->isNullValue());
}

// ----- LConstantFP

NodeProto<LConstantFP> LConstantFP::proto("ConstantFP");

void LConstantFP::init() {
  proto.inherit(LConstant::proto);
  proto.addMethod("isZero", &LConstantFP::isZero);
//  proto.addMethod("isNegative", &LConstantFP::isNegative);
  proto.addMethod("isExactlyValue", &LConstantFP::isExactlyValue);
}

// isZero()
Handle<Value> LConstantFP::isZero(const Arguments& args) {
  return Boolean::New(constantFP()->isZero());
}

// isNegative()
//Handle<Value> LConstantFP::isNegative(const Arguments& args) {
//  return Boolean::New(constantFP()->isNegative());
//}

// isExactlyValue(value: Number)
Handle<Value> LConstantFP::isExactlyValue(const Arguments& args) {
  CHECK_ARG_COUNT("isExactlyValue", 1, 1, "value: Number");
  CHECK_ARG_NUMBER(0);
  double value = args[0]->ToNumber()->Value();
  return Boolean::New(constantFP()->isExactlyValue(llvm::APFloat(value)));
}
