#include <v8.h>
#include <node.h>
#include "context.h"

using namespace v8;

Persistent<FunctionTemplate> NodeLContext::constructor;

inline Persistent<FunctionTemplate> makeConstructor(const char *name) {
  Local<FunctionTemplate> f = FunctionTemplate::New();
  Persistent<FunctionTemplate> proto = Persistent<FunctionTemplate>::New(f);
  proto->SetClassName(String::NewSymbol(name));
  proto->InstanceTemplate()->SetInternalFieldCount(1);
  return proto;
}

inline void addMethod(Handle<FunctionTemplate> ctor, const char *name, InvocationCallback cb) {
  Local<FunctionTemplate> f = FunctionTemplate::New(cb);
  ctor->InstanceTemplate()->Set(String::NewSymbol(name), f);
}

void NodeLContext::init() {
  HandleScope scope;

  constructor = makeConstructor("LLVMContext");
  addMethod(constructor, "newModule", newModule);
  constructor->InstanceTemplate()->Set(String::NewSymbol("msg"), String::New("Okay, that worked."));
}

Handle<Value> NodeLContext::create(llvm::LLVMContext& c) {
  HandleScope scope;

  Local<Object> jsobj = constructor->GetFunction()->NewInstance();
  (new NodeLContext(c))->Wrap(jsobj);
  return scope.Close(jsobj);
}

Handle<Value> NodeLContext::newModule(const Arguments& args) {
  HandleScope scope;
  NodeLContext *self = Unwrap<NodeLContext>(args.This());
  printf("id=%d\n", self->id);
  Local<String> rv = String::New("hello!");
  return scope.Close(rv);
}

//  v8::Local<v8::FunctionTemplate> templ = v8::FunctionTemplate::New(callback);
 //   target->PrototypeTemplate()->Set(v8::String::NewSymbol(name), templ);
