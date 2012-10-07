#include "basicblock.h"
#include "constant.h"
#include "context.h"
#include "executionengine.h"
#include "function.h"
#include "irbuilder.h"
#include "llvm.h"
#include "module.h"
#include "nativecallable.h"
#include "passmanager.h"
#include "type.h"

#include "llvm/Target/TargetData.h"
#include "llvm/Support/TargetSelect.h"
// warning! the following line is mandatory, even though the library will compile without it.
// it magically makes ExecutionEngine work.
#include "llvm/ExecutionEngine/JIT.h"

using namespace v8;

/*
 * manage all the proto init stuff here.
 */
extern "C" {
  static void init(Handle<Object> target) {
    // llvm itself requires initialization.
    llvm::InitializeNativeTarget();

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
    NativeCallable::init();
  }

  NODE_MODULE(nolove, init);
}
