#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Analysis/LoopPass.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
  struct LicmPass : public FunctionPass {
    static char ID;
    LicmPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      errs() << "Running LICM Simple on function: " << F.getName() << "\n";

      LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();

      for (Loop *L : LI) {
        BasicBlock *header = L->getHeader();
        errs() << "  Found loop with header: ";
        if (header)
          errs() << header->getName() << "\n";
        else
          errs() << "(no header)\n";

        // Ovde ćeš kasnije dodati detekciju loop-invariant instrukcija
      }

      return false; // ništa ne menjamo zasad
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.addRequired<LoopInfoWrapperPass>();
    }
  };
}

char LicmPass::ID = 0;
static RegisterPass<LicmPass> X("licm-pass", "Simple LICM Pass", false, false);
