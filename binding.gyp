{
  "variables": {
    "llvm_home": "/Users/robey/llvm"
  },
  "targets": [
    {
      "target_name": "llvm",
      "type": "<(library)",
      "sources": [
        "src/context.cpp",
        "src/llvm.cpp",
        "src/module.cpp"
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
        "-lLLVMCore",
        "-lLLVMSupport"
      ]
    }
  ]
}

