add_llvm_library( LLVMOurPass MODULE
  LICMPass.cpp
  LoopReducePass.cpp

  PLUGIN_TOOL
  opt
)
