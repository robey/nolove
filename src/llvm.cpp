#include "llvm.h"
#include "context.h"
#include "type.h"

using namespace v8;

void NodeLLVM::init(Handle<Object> target) {
  HandleScope scope;

  Handle<FunctionTemplate> f1 = FunctionTemplate::New(getGlobalContext);
  target->Set(String::NewSymbol("getGlobalContext"), f1->GetFunction());

  Handle<FunctionTemplate> f2 = FunctionTemplate::New(getFunctionType);
  target->Set(String::NewSymbol("getFunctionType"), f2->GetFunction());
}

// getGlobalContext()
Handle<Value> NodeLLVM::getGlobalContext(const Arguments& args) {
  return (new NodeLContext(llvm::getGlobalContext()))->handle_;
}

// getFunctionType(result: Type, optional params: Array<Type>, isVarArg: Boolean)
Handle<Value> NodeLLVM::getFunctionType(const Arguments& args) {
  CHECK_ARG_COUNT("getFunctionType", 2, 3, "result: Type, optional params: Array<Type>, isVarArg: Boolean");
  CHECK_ARG_TYPE(LType, 0);
  LType *resultType = LType::proto.unwrap(args[0]);
  if (args[1]->IsArray()) {
    Handle<Array> params = Handle<Array>::Cast(args[1]);
    std::vector<const llvm::Type *> paramTypes;
    CHECK_ARRAY_TYPE(LType, params);
    unwrapArrayRaw<LType>(params, paramTypes);
    return (new LFunctionType(resultType->wrapped, paramTypes, args[2]->BooleanValue()))->handle_;
  } else {
    return (new LFunctionType(resultType->wrapped, args[1]->BooleanValue()))->handle_;
  }
}
