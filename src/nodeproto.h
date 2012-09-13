#pragma once

#include <string>
#include <vector>
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

  static Handle<Value> throwTypeError(const std::string& message) {
    return v8::ThrowException(v8::Exception::TypeError(v8::String::New(message.c_str())));
  }

  static const char *utf8Arg(const Arguments& args, int index) {
    v8::String::Utf8Value name(args[index]->ToString());
    return *name;
  }

  static const char *utf8(Handle<String> s) {
    v8::String::Utf8Value value(s);
    return *value;
  }

  template <typename T>
  static void unwrapArray(Handle<Array> array, std::vector<T *>& vector) {
    for (unsigned int i = 0; i < array->Length(); i++) {
      Handle<Value> v = array->Get(i);
      vector.push_back(T::proto.unwrap(v));
    }
  }

  template <typename T, typename Wrapped>
  static void unwrapArrayRaw(Handle<Array> array, std::vector<Wrapped>& vector) {
    for (unsigned int i = 0; i < array->Length(); i++) {
      Handle<Value> v = array->Get(i);
      vector.push_back(T::proto.unwrap(v)->wrapped);
    }
  }
};

#define CHECK_ARG_COUNT(__name, __min, __max, __desc) \
  if (args.Length() < (__min) || args.Length() > (__max)) { \
    return throwError(__name " requires (" __desc ")"); \
  }

#define CHECK_ARG_TYPE(__type, __n) \
  if (! __type::proto.hasInstance(args[__n])) { \
    return throwTypeError(std::string("Argument " #__n " must be of type ") + __type::proto.className); \
  }

#define CHECK_ARG_NUMBER(__n) \
  if (! args[__n]->IsNumber()) { \
    return throwTypeError(std::string("Argument " #__n " must be a number")); \
  }

#define CHECK_ARRAY_TYPE(__type, __a) \
  for (unsigned int __i = 0; __i < (__a)->Length(); __i++) { \
    Handle<Value> __v = (__a)->Get(__i); \
    if (! __type::proto.hasInstance(__v)) { \
      return throwTypeError(std::string("Array items must be of type ") + __type::proto.className); \
    } \
  }

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
template <typename T, typename Wrapped>
class NodeWrapped : public node::ObjectWrap, public NodeHelper {
public:
  Wrapped wrapped;

  NodeWrapped(Wrapped obj) : wrapped(obj) {
    Local<Object> jsobj = T::proto.constructor->GetFunction()->NewInstance();
    Wrap(jsobj);
  }
};

