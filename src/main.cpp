#include <iostream>
#include "Lexer.h"
#include "Parser.h"
#include "Expression.h"
#include "Declaration.h"
#include "Statement.h"
#include <unistd.h>
#include <string>
#include <vector>
#include <fstream>
#include "mips32/Translator.h"
#include "mips32/Optimizer.h"

using std::cout;
using std::cerr;
using std::endl;
using std::vector;
using std::string;
using std::map;
using std::fstream;

int main(int argc, char** argv) {
	if(argc < 3) {
		cout << "mipsify expects two parameters: the input and output files." << endl;
	} else {
		if(access(argv[1], R_OK) == 0) {
			Lexer::lexFile(argv[1]);
			Program* p = runParser();
			if(p != NULL) {
				//cout << p->getPosition() << endl;
				map<string, const Declaration*> rootscope;
				bool valid = p->check(rootscope);
				if(valid) {
					//cout << "Valid: " << valid << endl;
					
					mips32::Translator translator;
					
					vector<mips32::Instruction*> instr = translator.translate(*p);
					
					double numIns = instr.size();
					
					mips32::optimize(instr);
					
					cout << "Optimizer was able to remove " << 100.0 * (1.0 - (instr.size() / numIns)) << "% of instructions." << endl;
					
					fstream out(argv[2], fstream::out);
					
					for(auto it = instr.begin(); it != instr.end(); it++) {
						out << **it;
						delete (*it);
					}
					
					out.close();
				} else {
					cout << "There were errors in the file." << endl;
				}
				
				delete p;
			} else {
				cout << "Encountered errors, exiting." << endl;
			}
		} else {
			cout << "Could not access file " << argv[1] << endl;
		}
		//Program comparison(vector<Declaration*>{new GlobalVarDeclarationInit(new IntType(),"x", new IntConstantExpression(5))});
		
		//cout << (comparison == (*p)) << endl;
	}
}