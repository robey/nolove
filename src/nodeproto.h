#pragma once

#include <string>
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

/**
 * helper functions
 */
class NodeHelper {
public:
  static Handle<Value> throwError(const std::string& message) {
    return v8::ThrowException(v8::Exception::Error(v8::String::New(message.c_str())));
  }

  static const char *utf8Arg(const Arguments& args, int index) {
    v8::String::Utf8Value name(args[index]->ToString());
    return *name;
  }

  // return v8::ThrowException(v8::Exception::TypeError(v8::String::New("...")));
  // -- not of the expected type
};

/**
 * This is meant to be a static member of a class that pairs with a js
 * class. The proto defines all the class methods in js, and can create
 * new js objects with the pairing set up.
 */
template <typename T, typename Wrapped>
class NodeProto {
public:
  typedef Handle<Value> (T::*Method)(const Arguments& args);

  Persistent<FunctionTemplate> constructor;

  static Handle<Value> trampoline(const Arguments& args) {
    Method method = reinterpret_cast<Suitcase<Method> *>(External::Unwrap(args.Data()))->item;
    // this is a bit evil. manual implementation of node's Unwrap:
    T *self = static_cast<T *>(args.This()->GetPointerFromInternalField(0));
    return (self->*method)(args);
  }

  NodeProto(const char *name) {
    Local<FunctionTemplate> f = FunctionTemplate::New();
    constructor = Persistent<FunctionTemplate>::New(f);
    constructor->SetClassName(String::NewSymbol(name));
    constructor->InstanceTemplate()->SetInternalFieldCount(1);
  }

  void addMethod(const char *name, Method method) {
    // in theory, this is a leak, but it's only done at startup, and needed forever.
    Suitcase<Method> *suitcase = new Suitcase<Method>(method);
    Local<FunctionTemplate> f = FunctionTemplate::New(trampoline, External::Wrap(suitcase));
    constructor->InstanceTemplate()->Set(String::NewSymbol(name), f);
  }

  void addField(const char *name, Handle<Value> value) {
    constructor->InstanceTemplate()->Set(String::NewSymbol(name), value);
  }
};

/**
 * Classes that use NodeProto must also subclass NodeWrapped so they can be
 * constructed.
 */
template <typename T, typename Wrapped>
class NodeWrapped : public node::ObjectWrap, public NodeHelper {
protected:
  Wrapped wrapped;

  NodeWrapped(Wrapped obj) : wrapped(obj) {
    Local<Object> jsobj = T::proto.constructor->GetFunction()->NewInstance();
    Wrap(jsobj);
  }
};

