#include <v8.h>
#include <node.h>
#include "context.h"

using namespace v8;

NodePrototype<NodeLContext> NodeLContext::proto("LLVMContext");

void NodeLContext::init() {
  HandleScope scope;

  proto.addMethod("newModule", newModule);
  proto.addMethod__("newModule__", &NodeLContext::newModule__);
  proto.addField("msg", String::New("Okay, that worked."));
}

Handle<Value> NodeLContext::create(llvm::LLVMContext& c) {
  HandleScope scope;

  Local<Object> jsobj = proto.create();
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

Handle<Value> NodeLContext::newModule__(const Arguments& args) {
  HandleScope scope;
  printf("id=%d\n", id);
  Local<String> rv = String::New("hello from crazy town!");
  return scope.Close(rv);
}

//  v8::Local<v8::FunctionTemplate> templ = v8::FunctionTemplate::New(callback);
 //   target->PrototypeTemplate()->Set(v8::String::NewSymbol(name), templ);
