#pragma once

#include <string>
#include <vector>
#include <v8.h>
#include <node.h>

using namespace v8;

/**
 * helper functions
 */
class NodeHelper {
public:
  template <typename T>
  static T *createWrapped(void *native) {
    T *myobj = new T();
    myobj->wrap(T::proto.create(), native);
    return myobj;
  }

  static void addObjectMethod(Handle<Object> obj, const char *name, InvocationCallback callback) {
    Local<FunctionTemplate> f = FunctionTemplate::New(callback);
    obj->Set(String::NewSymbol(name), f->GetFunction());
  }

  static void addObjectField(Handle<Object> obj, const char *name, Handle<Value> value) {
    obj->Set(String::NewSymbol(name), value);
  }

  static Handle<Value> throwError(const std::string& message) {
    return ThrowException(Exception::Error(String::New(message.c_str())));
  }

  static Handle<Value> throwTypeError(const std::string& message) {
    return ThrowException(Exception::TypeError(String::New(message.c_str())));
  }

  static const char *utf8Arg(const Arguments& args, int index) {
    String::Utf8Value name(args[index]->ToString());
    return *name;
  }

  static const char *utf8(Handle<String> s) {
    String::Utf8Value value(s);
    return *value;
  }

  template <class T>
  static inline T *unwrapNative(Handle<Object> handle) {
    return static_cast<T *>(handle->GetPointerFromInternalField(1));
  }

  template <typename T>
  static void unwrapArray(Handle<Array> array, std::vector<T *>& vector) {
    for (unsigned int i = 0; i < array->Length(); i++) {
      Handle<Value> v = array->Get(i);
      vector.push_back(T::proto.unwrap(v));
    }
  }

  template <typename A>
  static void unwrapArrayRaw(Handle<Array> array, std::vector<A *>& vector) {
    for (unsigned int i = 0; i < array->Length(); i++) {
      Handle<Object> obj = array->Get(i)->ToObject();
      vector.push_back(unwrapNative<A>(obj));
    }
  }
};

#define CHECK_ARG_COUNT(__name, __min, __max, __desc) \
  if (args.Length() < (__min) || args.Length() > (__max)) { \
    return NodeHelper::throwError(__name " requires (" __desc ")"); \
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
