#include <v8.h>
#include <node.h>
#include "context.h"

using namespace v8;

Persistent<FunctionTemplate> NodeLContext::prototypeObject;

void NodeLContext::init() {
  HandleScope scope;

  // create prototype
  Local<FunctionTemplate> f = FunctionTemplate::New();
  prototypeObject = Persistent<FunctionTemplate>::New(f);
  prototypeObject->SetClassName(String::NewSymbol("LLVMContext"));
  Local<ObjectTemplate> tp = prototypeObject->InstanceTemplate();
  tp->SetInternalFieldCount(1);
  Local<FunctionTemplate> f2 = FunctionTemplate::New(newModule);
  tp->Set(String::NewSymbol("newModule"), Persistent<FunctionTemplate>::New(f2));
  tp->Set(String::NewSymbol("msg"), String::New("Okay, that worked."));
}

Handle<Value> NodeLContext::create(llvm::LLVMContext& c) {
  HandleScope scope;

  Local<Object> obj = prototypeObject->GetFunction()->NewInstance();
  NodeLContext *me = new NodeLContext(c);
  me->Wrap(obj);

  return scope.Close(obj);
}

Handle<Value> NodeLContext::newModule(const Arguments& args) {
  HandleScope scope;
  Local<String> rv = String::New("hello!");
  return scope.Close(rv);
}
