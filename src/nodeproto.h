#pragma once

#include <string>
#include <vector>
#include <v8.h>
#include <node.h>
#include "llvm/LLVMContext.h"
#include "nodehelper.h"

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

/**
 * This is meant to be a static member of a class that pairs with a js
 * class. The proto defines all the class methods in js, and can create
 * new js objects with the pairing set up.
 */
template <typename T>
class NodeProto {
public:
  typedef Handle<Value> (T::*Method)(const Arguments& args);

  Persistent<FunctionTemplate> constructor;
  const char *className;

  static Handle<Value> trampoline(const Arguments& args) {
    Method method = reinterpret_cast<Suitcase<Method> *>(External::Unwrap(args.Data()))->item;
    // this is a bit evil. manual implementation of node's Unwrap:
    T *self = static_cast<T *>(args.This()->GetPointerFromInternalField(0));
    return (self->*method)(args);
  }

  NodeProto(const char *name) : className(name) {
    Local<FunctionTemplate> f = FunctionTemplate::New();
    constructor = Persistent<FunctionTemplate>::New(f);
    constructor->SetClassName(String::NewSymbol(name));
    // slot 0: pointer to our (node-llvm) object, stored by node::ObjectWrap
    // slot 1: pointer to a libllvm object
    constructor->InstanceTemplate()->SetInternalFieldCount(2);
  }

  void addMethod(const char *name, Method method) {
    // in theory, this is a leak, but it's only done at startup, and needed forever.
    Suitcase<Method> *suitcase = new Suitcase<Method>(method);
    Local<FunctionTemplate> f = FunctionTemplate::New(trampoline, External::Wrap(suitcase));
    constructor->PrototypeTemplate()->Set(String::NewSymbol(name), f);
  }

  void addField(const char *name, Handle<Value> value) {
    constructor->InstanceTemplate()->Set(String::NewSymbol(name), value);
  }

  Handle<Object> create() {
    return constructor->GetFunction()->NewInstance();
  }

  template <typename A>
  void inherit(NodeProto<A>& superclass) {
    constructor->Inherit(superclass.constructor);
  }

  bool hasInstance(Handle<Value> obj) {
    return obj->IsObject() && constructor->HasInstance(obj);
  }

  T *unwrap(Handle<Value> obj) {
    return node::ObjectWrap::Unwrap<T>(obj->ToObject());
  }
};

/**
 * Classes that use NodeProto must also subclass NodeWrapped so they can be
 * constructed.
 */
class NodeWrapped : public node::ObjectWrap, public NodeHelper {
public:
  void wrap(Handle<Object> obj, void *native) {
    Wrap(obj);
    // note that no attempt is made to free/delete the wrapped references.
    // we assume llvm is owning its own memory.
    handle_->SetPointerInInternalField(1, native);
  }

  template <typename A>
  A *wrapped() {
    return static_cast<A *>(handle_->GetPointerFromInternalField(1));
  }
};

