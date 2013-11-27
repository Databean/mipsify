#include "Optimizer.h"
#include "Instruction.h"
#include "Arithmetic.h"
#include <vector>
#include <map>
#include <stdexcept>

using std::vector;
using std::map;
using std::runtime_error;

namespace mips32 {
	
	/**
	 * Produces a new instruction that should produce the same result as an immediate binary operator.
	 */
	Instruction* replaceBinOpImmediate(BinOpImmediate* binOpImm, Instruction* left) {
		LoadImmediate* maybeLoadImm = dynamic_cast<LoadImmediate*>(left);
		if(maybeLoadImm) {
			if(binOpImm->getOp() == "addi") {
				return new LoadImmediate(binOpImm->destinationRegister(), binOpImm->getRight() + maybeLoadImm->getValue());
			} else if(binOpImm->getOp() == "andi") {
				return new LoadImmediate(binOpImm->destinationRegister(), binOpImm->getRight() & maybeLoadImm->getValue());
			} else if(binOpImm->getOp() == "ori") {
				return new LoadImmediate(binOpImm->destinationRegister(), binOpImm->getRight() | maybeLoadImm->getValue());
			} else if(binOpImm->getOp() == "slti") {
				return new LoadImmediate(binOpImm->destinationRegister(), binOpImm->getRight() > maybeLoadImm->getValue());
			} 
		}
		return binOpImm;
	}
	
	/**
	 * Produces a new instruction that should produce the same result as a binary operator.
	 */
	Instruction* replaceBinOp(BinOp* binOp, Instruction* left, Instruction* right) {
		LoadImmediate* maybeLoadImmLeft = dynamic_cast<LoadImmediate*>(left);
		LoadImmediate* maybeLoadImmRight = dynamic_cast<LoadImmediate*>(right);
		if(maybeLoadImmLeft && maybeLoadImmRight) {
			if(binOp->getOp() == "add") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() + maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "sub") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() - maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "and") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() & maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "or") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() | maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "xor") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() ^ maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "slt") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() < maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "mul") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() * maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "div") {
				return new LoadImmediate(binOp->destinationRegister(), maybeLoadImmLeft->getValue() / maybeLoadImmRight->getValue());
			} 
		} else if(maybeLoadImmLeft) {
			if(binOp->getOp() == "add") {
				return new BinOpImmediate("addi", binOp->destinationRegister(), binOp->getRight(), maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "and") {
				return new BinOpImmediate("andi", binOp->destinationRegister(), binOp->getRight(), maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "or") {
				return new BinOpImmediate("ori", binOp->destinationRegister(), binOp->getRight(), maybeLoadImmRight->getValue());
			} 
		} else if(maybeLoadImmRight) {
			if(binOp->getOp() == "add") {
				return new BinOpImmediate("addi", binOp->destinationRegister(), binOp->getLeft(), maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "sub") {
				return new BinOpImmediate("addi", binOp->destinationRegister(), binOp->getLeft(), -maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "and") {
				return new BinOpImmediate("andi", binOp->destinationRegister(), binOp->getLeft(), maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "or") {
				return new BinOpImmediate("ori", binOp->destinationRegister(), binOp->getLeft(), maybeLoadImmRight->getValue());
			} else if(binOp->getOp() == "slt") {
				return new BinOpImmediate("slti", binOp->destinationRegister(), binOp->getLeft(), maybeLoadImmRight->getValue());
			} 
		}
		return binOp;
	}
	
	/**
	 * Takes instructions that can be combined together, and replaces them with their evaluated versions.
	 */
	void compileTimeEval(vector<Instruction*>& instructions) {
		
		map<Register, Instruction*> sources;
		
		for(size_t i = 0; i < instructions.size(); i++) {
			if(dynamic_cast<ControlFlowInstruction*>(instructions[i])) {
				sources.clear();
				continue;
			}
			
			//Replaces binary immediate operators if possible with LoadImmediate instructions
			BinOpImmediate* maybeBinOpImm = dynamic_cast<BinOpImmediate*>(instructions[i]);
			if(maybeBinOpImm) {
				if(sources.count(maybeBinOpImm->getLeft())) {
					instructions[i] = replaceBinOpImmediate(maybeBinOpImm, sources[maybeBinOpImm->getLeft()]);
				}
				if(instructions[i] != maybeBinOpImm) {
					delete maybeBinOpImm;
				}
			}
			BinOp* maybeBinOp = dynamic_cast<BinOp*>(instructions[i]);
			if(maybeBinOp) {
				if(sources.count(maybeBinOp->getLeft()) && sources.count(maybeBinOp->getRight())) {
					instructions[i] = replaceBinOp(maybeBinOp, sources[maybeBinOp->getLeft()], sources[maybeBinOp->getRight()]);
				}
				if(instructions[i] != maybeBinOp) {
					delete maybeBinOp;
				}
			}
			StoreWord* maybeStoreWord = dynamic_cast<StoreWord*>(instructions[i]);
			if(maybeStoreWord) {
				if(sources.count(maybeStoreWord->getLocation())) {
					BinOpImmediate* maybeBinOpImm = dynamic_cast<BinOpImmediate*>(sources[maybeStoreWord->getLocation()]);
					if(maybeBinOpImm && maybeBinOpImm->getOp() == "addi" && maybeBinOpImm->destinationRegister() != maybeBinOpImm->getLeft()) {
						instructions[i] = new StoreWord(maybeStoreWord->getData(), maybeBinOpImm->getLeft(), maybeStoreWord->getOffset() + maybeBinOpImm->getRight());
					}
				}
				if(instructions[i] != maybeStoreWord) {
					delete maybeStoreWord;
				}
			}
			LoadWord* maybeLoadWord = dynamic_cast<LoadWord*>(instructions[i]);
			if(maybeLoadWord) {
				if(sources.count(maybeLoadWord->getLocation())) {
					BinOpImmediate* maybeBinOpImm = dynamic_cast<BinOpImmediate*>(sources[maybeLoadWord->getLocation()]);
					if(maybeBinOpImm && maybeBinOpImm->getOp() == "addi" && maybeBinOpImm->destinationRegister() != maybeBinOpImm->getLeft()) {
						instructions[i] = new LoadWord(maybeLoadWord->getData(), maybeBinOpImm->getLeft(), maybeLoadWord->getOffset() + maybeBinOpImm->getRight());
					}
				}
				if(instructions[i] != maybeLoadWord) {
					delete maybeLoadWord;
				}
			}
			
			if(instructions[i]->writesToRegister()) {
				sources[instructions[i]->destinationRegister()] = instructions[i];
			}
		}
	}
	
	/**
	 * Gets rid of any instructions that write to registers that are never read from until they are written again.
	 * Makes the assumption that after any instruction that affects control flow, a register is not used again, except for $ra, $sp, $a0, and $v0.
	 */
	void eliminateUnusedInstructions(vector<Instruction*>& instructions) {
		for(size_t i = 0; i < instructions.size(); i++) {
			if(instructions[i]->writesToRegister()) {
				Register r = instructions[i]->destinationRegister();
				bool used = (r == R_RA || r == R_SP || r == R_A0 || r == R_V0);
				for(size_t j = i + 1; j < instructions.size(); j++) {
					if(instructions[j]->readsRegister(r)) {
						used = true;
					}
					if(dynamic_cast<ControlFlowInstruction*>(instructions[j])) {
						break;
					}
					if(instructions[j]->writesToRegister() && instructions[j]->destinationRegister() == r) {
						break;
					}
				}
				if(!used) {
					delete instructions[i];
					instructions.erase(instructions.begin() + i);
					i--;
				}
			}
		}
	}
	
	/**
	 * Combines all implemented optimization methods into one convenient function call.
	 */
	void optimize(vector<Instruction*>& instructions) {
		compileTimeEval(instructions);
		eliminateUnusedInstructions(instructions);
	}
	
}