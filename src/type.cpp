#include "type.h"

using namespace v8;

// ----- LAbstractType

template <typename T, typename Wrapped>
void LAbstractType<T, Wrapped>::init(NodeProto<T, Wrapped> proto) {
  proto.addMethod("isDoubleType", &LAbstractType<T, Wrapped>::isDoubleType);
}

template <typename T, typename Wrapped>
Handle<Value> LAbstractType<T, Wrapped>::isDoubleType(const Arguments& args) {
  return v8::Boolean::New(this->wrapped->isDoubleTy());
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

//  proto.addMethod("dump", &NodeLModule::dump);
}
