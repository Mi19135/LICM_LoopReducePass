#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Pass.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/ScalarEvolutionExpressions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {

struct LoopReducePass : public FunctionPass {
    static char ID;
    LoopReducePass() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
        errs() << "Running Loop Reduce Pass on function: " << F.getName() << "\n";

        bool Changed = false;

        // informacije o petljama
        LoopInfo &LI = getAnalysis<LoopInfoWrapperPass>().getLoopInfo();
        ScalarEvolution &SE = getAnalysis<ScalarEvolutionWrapperPass>().getSE();

        // Prolazimo kroz sve petlje u funkciji
        for (Loop *L : LI) {
            errs() << "Found loop with header: " << L->getHeader()->getName() << "\n";

            // Lista petlji koje treba obraditi
            SmallVector<Loop*, 8> WorkList;
            WorkList.push_back(L);

            while (!WorkList.empty()) {
                Loop *Curr = WorkList.pop_back_val();

                BasicBlock *Header = Curr->getHeader();
                if (!Header) continue;

                // Prolazimo kroz sve blokove u petlji
                for (BasicBlock *BB : Curr->getBlocks()) {
                    for (Instruction &I : *BB) {
                        if (I.isTerminator()) continue;  // Preskacu se terminatorske instrukcije

                        if (isa<PHINode>(&I)) {
                            PHINode *PHI = cast<PHINode>(&I);
                            // Debug poruka za detekciju PHI čvorova
                            errs() << "Checking PHI node: " << *PHI << "\n";
                            if (isInductionVariable(PHI, SE)) {
                                errs() << "Identified induction variable: " << *PHI << "\n";
                                tryReduceLoop(PHI, SE, Curr, Changed);
                            }
                        }
                    }
                }

                // Dodajemo ugnjezdene petlje u WorkList
                for (Loop *SubLoop : Curr->getSubLoops())
                    WorkList.push_back(SubLoop);
            }
        }

        return Changed;
    }

    // provera da li je PHI indukciona promenljiva
    bool isInductionVariable(PHINode *PHI, ScalarEvolution &SE) {
        // Koristi SE da proveri da li je PHI indukciona promenljiva
        if (PHI->getNumIncomingValues() == 2) {
            Value *IncValue = PHI->getIncomingValue(0);
            if (SE.isSCEVable(IncValue->getType())) {
                const SCEV *Scev = SE.getSCEV(IncValue);
                if (auto *AddRecExpr = dyn_cast<SCEVAddRecExpr>(Scev)) {
                    errs() << "Found induction variable: " << *PHI << "\n";
                    return true;
                }
            }
        }
        return false;
    }

    // Funkcija za primenu redukcije petlje
    void tryReduceLoop(PHINode *PHI, ScalarEvolution &SE, Loop *Curr, bool &Changed) {
        // Premestiti vrednost iz petlje u preheader
        BasicBlock *Preheader = Curr->getLoopPreheader();
        if (Preheader) {
            PHI->moveBefore(Preheader->getTerminator());
            Changed = true;
            errs() << "Reducing loop with PHI node: " << *PHI << "\n";
        }
    }

    void getAnalysisUsage(AnalysisUsage &AU) const override {
        AU.addRequired<LoopInfoWrapperPass>();
        AU.addRequired<ScalarEvolutionWrapperPass>();
    }
};

}

char LoopReducePass::ID = 0;
static RegisterPass<LoopReducePass> X("loop-reduce-pass", "Loop Reduction Pass", false, false);
