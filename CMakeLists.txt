add_llvm_library( LLVMOurPass MODULE
  LICMPass.cpp

  PLUGIN_TOOL
  opt
)
