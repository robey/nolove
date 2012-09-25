#include "basicblock.h"
#include "constant.h"
#include "context.h"
#include "executionengine.h"
#include "function.h"
#include "irbuilder.h"
#include "llvm.h"
#include "module.h"
#include "passmanager.h"
#include "type.h"

using namespace v8;

/*
 * manage all the proto init stuff here.
 */
extern "C" {
  static void init(Handle<Object> target) {
    NodeLLVM::init(target);
    LArgument::init();
    LBasicBlock::init();
    LConstant::init();
    LConstantFP::init();
    LContext::init();
    LExecutionEngine::init();
    LFunction::init();
    LFunctionPassManager::init();
    LFunctionType::init();
    LIRBuilder::init();
    LModule::init();
    LPass::init();
    LTargetData::init();
    LType::init();
    LValue::init();
  }

  NODE_MODULE(llvm, init);
}
