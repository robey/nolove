{
  "variables": {
    "llvm_home": "/usr/local/llvm",
    "llvm_config": "<(llvm_home)/bin/llvm-config"
  },
  "targets": [
    {
      "target_name": "nolove",
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
        "src/nativecallable.cpp",
        "src/passmanager.cpp",
        "src/type.cpp",
        "src/value.cpp"
      ],
      "defines": [
        "__STDC_LIMIT_MACROS=1",
        "__STDC_CONSTANT_MACROS=1"
      ],
      "include_dirs": [
        "<!@(<(llvm_config) --includedir)"
      ],
      "libraries": [
        "<!@(<(llvm_config) --ldflags)",
        "<!@(<(llvm_config) --libs core jit native)"
      ]
    }
  ]
}
