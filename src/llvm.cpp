#include "llvm.h"
#include "context.h"
#include "globals.h"
#include "passmanager.h"
#include "type.h"

#include "llvm/PassManager.h"
#include "llvm/Analysis/Passes.h"

using namespace v8;

void NodeLLVM::init(Handle<Object> target) {
  addObjectMethod(target, "getGlobalContext", &getGlobalContext);
  addObjectMethod(target, "getFunctionType", &getFunctionType);

  addObjectMethod(target, "createBasicAliasAnalysisPass", &createBasicAliasAnalysisPass);

  Handle<Object> linkage = Object::New();
  LLinkage::init(linkage);
  addObjectField(target, "Linkage", linkage);
}

// getGlobalContext()
Handle<Value> NodeLLVM::getGlobalContext(const Arguments& args) {
  return LContext::create(&(llvm::getGlobalContext()))->handle_;
}

// getFunctionType(result: Type, optional params: Array<Type>, isVarArg: Boolean)
Handle<Value> NodeLLVM::getFunctionType(const Arguments& args) {
  CHECK_ARG_COUNT("getFunctionType", 2, 3, "result: Type, optional params: Array<Type>, isVarArg: Boolean");
  CHECK_ARG_TYPE(LType, 0);
  LType *resultType = LType::proto.unwrap(args[0]);
  if (args[1]->IsArray()) {
    Handle<Array> params = Handle<Array>::Cast(args[1]);
    std::vector<llvm::Type *> paramTypes;
    CHECK_ARRAY_TYPE(LType, params);
    unwrapArrayRaw(params, paramTypes);
    return LFunctionType::create(resultType->type(), paramTypes, args[2]->BooleanValue())->handle_;
  } else {
    return LFunctionType::create(resultType->type(), args[1]->BooleanValue())->handle_;
  }
}

Handle<Value> NodeLLVM::createBasicAliasAnalysisPass(const Arguments& args) {
  return LPass::create(llvm::createBasicAliasAnalysisPass())->handle_;
}
