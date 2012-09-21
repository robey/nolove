#include "value.h"

using namespace v8;

NodeProto<LValue> LValue::proto("Value");

void LValue::init() {
  proto.addMethod("getType", &LValue::getType);
  proto.addMethod("hasName", &LValue::hasName);
  proto.addMethod("getName", &LValue::getName);
  proto.addMethod("setName", &LValue::setName);
  proto.addMethod("toString", &LValue::toString);
}

Handle<Value> LValue::getType(const Arguments& args) {
  return LType::create(value()->getType())->handle_;
}

Handle<Value> LValue::hasName(const Arguments& args) {
  return Boolean::New(value()->hasName());
}

Handle<Value> LValue::getName(const Arguments& args) {
  return String::New(value()->getName().data());
}

Handle<Value> LValue::setName(const Arguments& args) {
  CHECK_ARG_COUNT("setName", 1, 1, "name: String");
  String::Utf8Value name(args[0]->ToString());
  value()->setName(*name);
  return Undefined();
}

Handle<Value> LValue::toString(const Arguments& args) {
  std::string s("<Value ");
  llvm::raw_string_ostream os(s);
  value()->print(os);
  os << ">";
  return String::New(os.str().c_str());
}
