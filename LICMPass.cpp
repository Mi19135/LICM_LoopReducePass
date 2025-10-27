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
           // errs() << "  Found loop with header: " << L->getHeader()->getName() << "\n";
            SmallVector<Loop*, 8> WorkList;
            WorkList.push_back(L);
           
            while (!WorkList.empty()) {
              Loop *Curr = WorkList.pop_back_val();
            
              BasicBlock *Header = Curr->getHeader();
              BasicBlock *Preheader = Curr->getLoopPreheader();
              if (!Header) continue;
              
              // Ispis tipa petlje
              BasicBlock *Latch = Curr->getLoopLatch();
              bool IsDoWhile = Latch && Curr->isLoopExiting(Latch);
              bool IsNested = Curr->getParentLoop() != nullptr;
              errs() << "Detected " << (IsNested ? "nested " : "")
                     << (IsDoWhile ? "do-while" : "while")
                     << " loop: " << Header->getName() << "\n";
              
              
              
              if (!Preheader) {
                      errs() << "    Loop has no preheader — skipping LICM.\n";
                      continue;
              }
              
              

              SmallVector<Instruction*, 8> toMove;

              for (BasicBlock *BB : Curr->getBlocks()) {
                  for (Instruction &I : *BB) {
                      if (I.isTerminator()) continue; // ne pomeramo terminatore

                      bool invariant = true;
                      for (Use &U : I.operands()) {
                          if (Instruction *OpInst = dyn_cast<Instruction>(U.get())) {
                              if (Curr->contains(OpInst)) {
                                  invariant = false;
                                  break;
                              }
                          }
                      }

               // dodatni filter: ne pomeramo load/store iz petlje na mutable adresu
                      if (invariant && (isa<LoadInst>(&I) || isa<StoreInst>(&I))) {
                           if (Value *Ptr = I.getOperand(0)) {
                              if (Instruction *PtrInst = dyn_cast<Instruction>(Ptr)) {
                                  if (Curr->contains(PtrInst)) {
                                      invariant = false;
                                  }
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
            
            // Dodaj ugnježdene petlje u WorkList
                for (Loop *SubLoop : Curr->getSubLoops())
                    WorkList.push_back(SubLoop);
            
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
