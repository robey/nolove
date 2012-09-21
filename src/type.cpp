#include "llvm/Support/raw_ostream.h"
#include "type.h"

using namespace v8;

// ----- LType

NodeProto<LType> LType::proto("Type");

void LType::init() {
  proto.addMethod("isDoubleType", &LType::isDoubleType);
  proto.addMethod("isFunctionType", &LType::isFunctionType);
  proto.addMethod("toString", &LType::toString);
}

Handle<Value> LType::isDoubleType(const Arguments& args) {
  return Boolean::New(type()->isDoubleTy());
}

Handle<Value> LType::isFunctionType(const Arguments& args) {
  return Boolean::New(type()->isFunctionTy());
}

Handle<Value> LType::toString(const Arguments& args) {
  std::string s("<Type ");
  llvm::raw_string_ostream os(s);
  type()->print(os);
  os << ">";
  return String::New(os.str().c_str());
}

// ----- LFunctionType

NodeProto<LFunctionType> LFunctionType::proto("FunctionType");

void LFunctionType::init() {
  proto.inherit(LType::proto);
  proto.addMethod("isVarArg", &LFunctionType::isVarArg);
  proto.addMethod("getNumParams", &LFunctionType::getNumParams);
  proto.addMethod("getParamType", &LFunctionType::getParamType);
}

Handle<Value> LFunctionType::isVarArg(const Arguments& args) {
  return Boolean::New(functionType()->isVarArg());
}

Handle<Value> LFunctionType::getNumParams(const Arguments& args) {
  return Integer::New(functionType()->getNumParams());
}

Handle<Value> LFunctionType::getParamType(const Arguments& args) {
  CHECK_ARG_COUNT("getParamType", 1, 1, "index: Number");
  CHECK_ARG_NUMBER(0);
  unsigned int index = (unsigned int) args[0]->ToNumber()->Value();
  return LType::create(functionType()->getParamType(index))->handle_;
}
