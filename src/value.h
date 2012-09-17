#pragma once

#include <sstream>
#include <v8.h>
#include <node.h>
#include "llvm/Value.h"
#include "llvm/Support/raw_ostream.h"
#include "nodeproto.h"
#include "type.h"

using namespace v8;

/**
 * In LLVM, almost everything descends from this interface.
 */
template <typename T, typename Wrapped>
class LValue : public NodeWrapped<T, Wrapped *> {
public:
  static void init(NodeProto<T, Wrapped *>& proto);

  LValue(Wrapped *wrapped) : NodeWrapped<T, Wrapped *>(wrapped) { }

  Handle<Value> getType(const Arguments& args);
  Handle<Value> hasName(const Arguments& args);
  Handle<Value> getName(const Arguments& args);
  Handle<Value> setName(const Arguments& args);
  Handle<Value> toString(const Arguments& args);
};

// i'm really sorry about this.
// c++ has bugs that require template methods to be defined in headers.

template <typename T, typename Wrapped>
void LValue<T, Wrapped>::init(NodeProto<T, Wrapped *>& proto) {
  proto.addMethod("getType", &LValue::getType);
  proto.addMethod("hasName", &LValue::hasName);
  proto.addMethod("getName", &LValue::getName);
  proto.addMethod("setName", &LValue::setName);
  proto.addMethod("toString", &LValue::toString);
}

template <typename T, typename Wrapped>
Handle<Value> LValue<T, Wrapped>::getType(const Arguments& args) {
  return (new LType(this->wrapped->getType()))->handle_;
}

template <typename T, typename Wrapped>
Handle<Value> LValue<T, Wrapped>::hasName(const Arguments& args) {
  return Boolean::New(this->wrapped->hasName());
}

template <typename T, typename Wrapped>
Handle<Value> LValue<T, Wrapped>::getName(const Arguments& args) {
  return String::New(this->wrapped->getName().data());
}

template <typename T, typename Wrapped>
Handle<Value> LValue<T, Wrapped>::setName(const Arguments& args) {
  CHECK_ARG_COUNT("setName", 1, 1, "name: String");
  String::Utf8Value name(args[0]->ToString());
  this->wrapped->setName(*name);
  return Undefined();
}

template <typename T, typename Wrapped>
Handle<Value> LValue<T, Wrapped>::toString(const Arguments& args) {
  std::string s("<Value ");
  llvm::raw_string_ostream os(s);
  this->wrapped->print(os);
  os << ">";
  return String::New(os.str().c_str());
}
