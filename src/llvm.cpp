#include "llvm.h"
#include "context.h"
#include "globals.h"
#include "type.h"

using namespace v8;

void NodeLLVM::init(Handle<Object> target) {
  addObjectMethod(target, "getGlobalContext", &getGlobalContext);
  addObjectMethod(target, "getFunctionType", &getFunctionType);

  Handle<Object> linkage = Object::New();
  LLinkage::init(linkage);
  addObjectField(target, "Linkage", linkage);
}

// getGlobalContext()
Handle<Value> NodeLLVM::getGlobalContext(const Arguments& args) {
  return (new LContext(llvm::getGlobalContext()))->handle_;
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
