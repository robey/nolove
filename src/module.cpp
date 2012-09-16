#include <v8.h>
#include <node.h>
#include "module.h"
#include "function.h"

using namespace v8;

NodeProto<NodeLModule, llvm::Module *> NodeLModule::proto("Module");

void NodeLModule::init() {
  proto.addField("msg", String::New("I am a module."));
  proto.addMethod("getModuleIdentifier", &NodeLModule::getModuleIdentifier);
  proto.addMethod("getDataLayout", &NodeLModule::getDataLayout);
  proto.addMethod("getTargetTriple", &NodeLModule::getTargetTriple);
  proto.addMethod("dump", &NodeLModule::dump);
}

Handle<Value> NodeLModule::getModuleIdentifier(const Arguments& args) {
  return String::New(wrapped->getModuleIdentifier().c_str());
}

Handle<Value> NodeLModule::getDataLayout(const Arguments& args) {
  return String::New(wrapped->getDataLayout().c_str());
}

Handle<Value> NodeLModule::getTargetTriple(const Arguments& args) {
  return String::New(wrapped->getTargetTriple().c_str());
}

Handle<Value> NodeLModule::dump(const Arguments& args) {
  wrapped->dump();
  return v8::Undefined();
}

// newFunction(type: FunctionType, linkage: Int, name: String)
Handle<Value> NodeLModule::newFunction(const Arguments& args) {
  CHECK_ARG_COUNT("newFunction", 3, 3, "type: FunctionType, linkage: Int, name: String");
  CHECK_ARG_TYPE(LFunctionType, 0);
  CHECK_ARG_NUMBER(1);
  LFunctionType *type = LFunctionType::proto.unwrap(args[0]);
  unsigned int linkage = (unsigned int) args[1]->ToNumber()->Value();
  String::Utf8Value name(args[2]->ToString());
  return (new LFunction(type->wrapped, (llvm::Function::LinkageTypes) linkage, *name, wrapped))->handle_;
}

/*
Endianness   getEndianness () const
   Target endian information. 
PointerSize   getPointerSize () const
   Target Pointer Size information. 
LLVMContext &   getContext () const
const std::string &   getModuleInlineAsm () const
*/



/*
Function *FunctionAST::Codegen() {
  NamedValues.clear();
  
  Function *TheFunction = Proto->Codegen();
  if (TheFunction == 0)
    return 0;
  
  // Create a new basic block to start insertion into.
  BasicBlock *BB = BasicBlock::Create(getGlobalContext(), "entry", TheFunction);
  Builder.SetInsertPoint(BB);
  
  if (Value *RetVal = Body->Codegen()) {
    // Finish off the function.
    Builder.CreateRet(RetVal);

    // Validate the generated code, checking for consistency.
    verifyFunction(*TheFunction);

    return TheFunction;
  }
  
  // Error reading body, remove function.
  TheFunction->eraseFromParent();
  return 0;
}*/
