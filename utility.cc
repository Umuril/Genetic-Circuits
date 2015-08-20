#include "utility.h"

bool exec(node root,std::deque<bool> & input,std::vector<node> & gate){
	switch(root.oper){
		case 0: // 000  NOTHING
			return input[root.a];
			break;
		case 1: // 001  AND
			return exec(gate[root.a],input,gate) & exec(gate[root.b],input,gate);
			break;
		case 2: // 010  OR
			return exec(gate[root.a],input,gate) | exec(gate[root.b],input,gate);
			break;
		case 3: // 011  XOR
			return exec(gate[root.a],input,gate) ^ exec(gate[root.b],input,gate);
			break;
		case 4: // 100  NOT
			return ~exec(gate[root.a],input,gate);
			break;
		case 5: // 101  NAND
			return ~(exec(gate[root.a],input,gate) & exec(gate[root.b],input,gate));
			break;
		case 6: // 110  NOR
			return ~(exec(gate[root.a],input,gate) | exec(gate[root.b],input,gate));
			break;
		case 7: // 111  XNOR
			return ~(exec(gate[root.a],input,gate) ^ exec(gate[root.b],input,gate));
			break;
		default:
			return false;
			break;
	}
}

int fitness(std::vector<node> &gate, std::vector<size_t> &root, const size_t &input_lenght,const std::vector< std::vector<bool> > &output){
	std::deque<bool> input(input_lenght);
	int solution = 0;
	
	for(int i = 0; i < (1 << input.size()); i++){
		for(size_t j = 0; j < input.size(); j++)
			input[j] = ((i >> j) & 1);
		for(size_t j = 0; j < root.size(); j++)
			if(exec(gate[root[j]],input,gate) == output[j][i])
				solution += 100;
	}
	
	return solution - gate.size() + input_lenght;
}
