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
  if (args.Length() < 2 || args.Length() > 3) {
    return throwError("getFunctionType requires (result: Type, optional params: Array<Type>, isVarArg: Boolean)");
  }

  // LFunctionType(const llvm::Type *result, const std::vector<const llvm::Type *>& params, bool isVarArg)

//  if (!args[0].IsObject()) {
//    return thro
//  }
  return v8::Undefined();
}
