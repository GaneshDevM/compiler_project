#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instructions.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

namespace {
struct MemoryInstructionCounter : public FunctionPass {
  static char ID;
  int count=1;
  MemoryInstructionCounter() : FunctionPass(ID) {}
  
  bool runOnFunction(Function &F) override {
    errs() << "Function " << F.getName() << ":\n";
    
    for (auto& BB : F) {
      errs() << "Basic Block ID: " << count++ << "\n";
      unsigned memoryInstructions = 0;
      unsigned nonMemoryInstructions = 0;

      for (auto& I : BB) {
        if (I.mayReadOrWriteMemory()) {
          memoryInstructions++;
        } else {
          nonMemoryInstructions++;
        }
      }

      errs() << "Memory Instructions: " << memoryInstructions << "\n";
      errs() << "Non-Memory Instructions: " << nonMemoryInstructions << "\n";
    }

    errs() << "\n";
    return false;
  }
};
}

char MemoryInstructionCounter::ID = 0;
static RegisterPass<MemoryInstructionCounter> X("memory-instruction-counter", "Count memory and non-memory instructions in basic blocks");
