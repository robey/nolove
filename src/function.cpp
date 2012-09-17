#include <v8.h>
#include <node.h>
#include "function.h"
#include "globals.h"

using namespace v8;

// ----- LFunction

NodeProto<LFunction, llvm::Function *> LFunction::proto("Function");

void LFunction::init() {
  LValue::init(proto);
}

// ----- LArgument

NodeProto<LArgument, llvm::Argument&> LArgument::proto("Argument");

void LArgument::init() {
}
