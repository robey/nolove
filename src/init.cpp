#include "llvm.h"
#include "context.h"
#include "module.h"
#include "type.h"

using namespace v8;

/*
 * manage all the proto init stuff here.
 */
extern "C" {
  static void init(Handle<Object> target) {
    NodeLLVM::init(target);
    LContext::init();
    LModule::init();
    LType::init();
    LFunctionType::init();
  }

  NODE_MODULE(llvm, init);
}
