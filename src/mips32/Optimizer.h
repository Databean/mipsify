#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include "Instruction.h"
#include "Arithmetic.h"
#include <vector>

namespace mips32 {
	
	void compileTimeEval(std::vector<Instruction*>& instructions);
	void eliminateUnusedInstructions(std::vector<Instruction*>& instructions);
	void optimize(std::vector<Instruction*>& instructions);
	
}

#endif