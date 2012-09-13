#include "llvm/Support/raw_ostream.h"
#include "type.h"

using namespace v8;

// ----- LAbstractType

template <typename T, typename Wrapped>
void LAbstractType<T, Wrapped>::init(NodeProto<T, Wrapped> proto) {
  proto.addMethod("isDoubleType", &LAbstractType<T, Wrapped>::isDoubleType);
  proto.addMethod("isFunctionType", &LAbstractType<T, Wrapped>::isFunctionType);
  proto.addMethod("toString", &LAbstractType<T, Wrapped>::toString);
}

template <typename T, typename Wrapped>
Handle<Value> LAbstractType<T, Wrapped>::isDoubleType(const Arguments& args) {
  return v8::Boolean::New(this->wrapped->isDoubleTy());
}

template <typename T, typename Wrapped>
Handle<Value> LAbstractType<T, Wrapped>::isFunctionType(const Arguments& args) {
  return v8::Boolean::New(this->wrapped->isFunctionTy());
}

template <typename T, typename Wrapped>
Handle<Value> LAbstractType<T, Wrapped>::toString(const Arguments& args) {
  std::string s("<Type ");
  llvm::raw_string_ostream os(s);
  this->wrapped->print(os);
  os << ">";
  return v8::String::New(os.str().c_str());
}

// ----- LType

NodeProto<LType, const llvm::Type *> LType::proto("Type");

void LType::init() {
  LAbstractType::init(proto);
}

// ----- LFunctionType

NodeProto<LFunctionType, llvm::FunctionType *> LFunctionType::proto("FunctionType");

void LFunctionType::init() {
  LAbstractType::init(proto);

  proto.addMethod("isVarArg", &LFunctionType::isVarArg);
  proto.addMethod("getNumParams", &LFunctionType::getNumParams);
  proto.addMethod("getParamType", &LFunctionType::getParamType);
}

Handle<Value> LFunctionType::isVarArg(const Arguments& args) {
  return v8::Boolean::New(wrapped->isVarArg());
}

Handle<Value> LFunctionType::getNumParams(const Arguments& args) {
  return v8::Integer::New(wrapped->getNumParams());
}

Handle<Value> LFunctionType::getParamType(const Arguments& args) {
  CHECK_ARG_COUNT("getParamType", 1, 1, "index: Number");
  CHECK_ARG_NUMBER(0);
  unsigned int index = (unsigned int) args[0]->ToNumber()->Value();
  return (new LType(wrapped->getParamType(index)))->handle_;
}
