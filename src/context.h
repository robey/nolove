#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"

using namespace v8;


class NodePrototype {
private:
  Persistent<FunctionTemplate> constructor;

public:
  NodePrototype(const char *name) {
    Local<FunctionTemplate> f = FunctionTemplate::New();
    constructor = Persistent<FunctionTemplate>::New(f);
    constructor->SetClassName(String::NewSymbol(name));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
  }

  void addMethod(const char *name, InvocationCallback cb) {
    Local<FunctionTemplate> f = FunctionTemplate::New(cb);
    constructor->InstanceTemplate()->Set(String::NewSymbol(name), f);
  }

  Local<Object> create() {
    return constructor->GetFunction()->NewInstance();
  }
};


class NodeLContext : node::ObjectWrap {
private:
  llvm::LLVMContext& llvmContext;
  int id;

  static Persistent<FunctionTemplate> constructor;

public:
  NodeLContext(llvm::LLVMContext& c) : llvmContext(c), id(23) { }

  static void init();
  static Handle<Value> create(llvm::LLVMContext& c);
  static Handle<Value> newModule(const Arguments& args);
};
