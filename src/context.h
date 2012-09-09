#pragma once

#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"

using namespace v8;

/*
 * somewhat ridiculous: C++ doesn't allow casting method pointers to/from
 * (void *) because it allows compilers to make method pointers be larger
 * than a pointer!
 */
template <typename T>
class Suitcase {
public:
  T item;

  Suitcase(T x) : item(x) { }
};

template <typename T>
class NodePrototype {
public:
  typedef Handle<Value> (T::*Method)(const Arguments& args);

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

  void addMethod__(const char *name, Method method) {
    // in theory, this is a leak, but it's only done at startup, and needed forever.
    Suitcase<Method> *suitcase = new Suitcase<Method>(method);
    Local<FunctionTemplate> f = FunctionTemplate::New(trampoline, External::Wrap(suitcase));
    constructor->InstanceTemplate()->Set(String::NewSymbol(name), f);
  }

  static Handle<Value> trampoline(const Arguments& args) {
    Method method = reinterpret_cast<Suitcase<Method> *>(External::Unwrap(args.Data()))->item;
    // this is a bit evil. manual implementation of node's Unwrap:
    T *self = static_cast<T *>(args.This()->GetPointerFromInternalField(0));
    return (self->*method)(args);
  }

  void addField(const char *name, Handle<Value> value) {
    constructor->InstanceTemplate()->Set(String::NewSymbol(name), value);
  }

  Local<Object> create() {
    return constructor->GetFunction()->NewInstance();
  }
};


class NodeLContext : node::ObjectWrap {
private:
  llvm::LLVMContext& llvmContext;
  int id;

  static NodePrototype<NodeLContext> proto;

public:
  NodeLContext(llvm::LLVMContext& c) : llvmContext(c), id(23) { }

  static void init();
  static Handle<Value> create(llvm::LLVMContext& c);
  static Handle<Value> newModule(const Arguments& args);
  Handle<Value> newModule__(const Arguments& args);
};
