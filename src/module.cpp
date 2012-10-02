#include <v8.h>
#include <node.h>
#include "executionengine.h"
#include "module.h"
#include "function.h"
#include "passmanager.h"

using namespace v8;

NodeProto<LModule> LModule::proto("Module");

void LModule::init() {
  proto.addField("msg", String::New("I am a module."));
  proto.addMethod("getModuleIdentifier", &LModule::getModuleIdentifier);
  proto.addMethod("getDataLayout", &LModule::getDataLayout);
  proto.addMethod("getTargetTriple", &LModule::getTargetTriple);
  proto.addMethod("dump", &LModule::dump);
  proto.addMethod("newFunction", &LModule::newFunction);
  proto.addMethod("newExecutionEngine", &LModule::newExecutionEngine);
  proto.addMethod("newFunctionPassManager", &LModule::newFunctionPassManager);
}

Handle<Value> LModule::getModuleIdentifier(const Arguments& args) {
  return String::New(module()->getModuleIdentifier().c_str());
}

Handle<Value> LModule::getDataLayout(const Arguments& args) {
  return String::New(module()->getDataLayout().c_str());
}

Handle<Value> LModule::getTargetTriple(const Arguments& args) {
  return String::New(module()->getTargetTriple().c_str());
}

Handle<Value> LModule::dump(const Arguments& args) {
  module()->dump();
  return v8::Undefined();
}

// newFunction(type: FunctionType, linkage: Int, name: String)
Handle<Value> LModule::newFunction(const Arguments& args) {
  CHECK_ARG_COUNT("newFunction", 3, 3, "type: FunctionType, linkage: Int, name: String");
  CHECK_ARG_TYPE(LFunctionType, 0);
  CHECK_ARG_NUMBER(1);
  LFunctionType *type = LFunctionType::proto.unwrap(args[0]);
  unsigned int linkage = (unsigned int) args[1]->ToNumber()->Value();
  return LFunction::create(type->functionType(), (llvm::Function::LinkageTypes) linkage, utf8Arg(args, 2), module())->handle_;
}

// newExecutionEngine()
Handle<Value> LModule::newExecutionEngine(const Arguments& args) {
  return LExecutionEngine::create(module())->handle_;
}

Handle<Value> LModule::newFunctionPassManager(const Arguments& args) {
  return LFunctionPassManager::create(module())-> handle_;
}

/*
Endianness   getEndianness () const
   Target endian information. 
PointerSize   getPointerSize () const
   Target Pointer Size information. 
LLVMContext &   getContext () const
const std::string &   getModuleInlineAsm () const
*/
