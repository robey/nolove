{
  "variables": {
    "llvm_home": "/Users/robey/llvm"
  },
  "targets": [
    {
      "target_name": "llvm",
      "type": "<(library)",
      "sources": [
        "src/llvm.cpp"
      ],
      "include_dirs": [
        "<(llvm_home)/include"
      ],
      "libraries": [
        "-L<(llvm_home)/lib",
        "-lLLVMCore"
      ]
    }
  ]
}

