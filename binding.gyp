{
  "variables": {
    "llvm_home": "/Users/robey/llvm"
  },
  "targets": [
    {
      "target_name": "llvm",
      "type": "<(library)",
      "sources": [
        "src/basicblock.cpp",
        "src/constant.cpp",
        "src/context.cpp",
        "src/executionengine.cpp",
        "src/function.cpp",
        "src/globals.cpp",
        "src/init.cpp",
        "src/instruction.cpp",
        "src/irbuilder.cpp",
        "src/llvm.cpp",
        "src/module.cpp",
        "src/passmanager.cpp",
        "src/type.cpp",
        "src/value.cpp"
      ],
      "defines": [
        "__STDC_LIMIT_MACROS=1",
        "__STDC_CONSTANT_MACROS=1"
      ],
      "include_dirs": [
        "<(llvm_home)/include"
      ],
      "libraries": [
        "-L<(llvm_home)/lib",
        "-lLLVMJIT",
        "-lLLVMExecutionEngine",
        "-lLLVMX86Disassembler",
        "-lLLVMX86AsmParser",
        "-lLLVMX86CodeGen",
        "-lLLVMSelectionDAG",
        "-lLLVMAsmPrinter",
        "-lLLVMMCParser",
        "-lLLVMCodeGen",
        "-lLLVMScalarOpts",
        "-lLLVMInstCombine",
        "-lLLVMTransformUtils",
        "-lLLVMipa",
        "-lLLVMAnalysis",
        "-lLLVMTarget",
        "-lLLVMX86AsmPrinter",
        "-lLLVMX86Utils",
        "-lLLVMX86Info",
        "-lLLVMMC",
        "-lLLVMCore",
        "-lLLVMSupport"
      ]
    }
  ]
}
