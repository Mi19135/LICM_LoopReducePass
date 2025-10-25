#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct LICMPass : public FunctionPass {
    static char ID;
    LICMPass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
        errs() << "Running LICM Simple on function: " << F.getName() << "\n";

        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        bool Changed = false;

        for (Loop *L : LI) {
            errs() << "  Found loop with header: " << L->getHeader()->getName() << "\n";
            BasicBlock *Preheader = L->getLoopPreheader();
            if (!Preheader) continue;

            SmallVector<Instruction*, 8> toMove;

            for (BasicBlock *BB : L->getBlocks()) {
                for (Instruction &I : *BB) {
                    if (I.isTerminator()) continue; // ne pomeramo terminatore

                    bool invariant = true;
                    for (Use &U : I.operands()) {
                        if (Instruction *OpInst = dyn_cast<Instruction>(U.get())) {
                            if (L->contains(OpInst)) {
                                invariant = false;
                                break;
                            }
                        }
                    }

                    if (invariant) {
                        errs() << "    Invariant instruction:   " << I << "\n";
                        toMove.push_back(&I);
                    }
                }
            }

            // premesti invariantne instrukcije u preheader
            for (Instruction *I : toMove) {
                I->moveBefore(Preheader->getTerminator());
                Changed = true;
            }
        }

        return Changed;
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
        AU.addRequired<LoopInfoWrapperPass>();
    }
};

}

char LICMPass::ID = 0;
static RegisterPass<LICMPass> X("licm-pass", "Simple LICM Pass", false, false);
