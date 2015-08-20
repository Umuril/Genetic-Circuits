#include "utility.h"

bool exec(node root){
	switch(root.oper){
		case 0: // 000  NOTHING
			return *((bool *)(root.a));
			break;
		case 1: // 001  AND
			return exec(*((node *)(root.a))) & exec(*((node *)(root.b)));
			break;
		case 2: // 010  OR
			return exec(*((node *)(root.a))) | exec(*((node *)(root.b)));
			break;
		case 3: // 011  XOR
			return exec(*((node *)(root.a))) ^ exec(*((node *)(root.b)));
			break;
		case 4: // 100  NOT
			return (bool)~(*((bool *)root.a));
			break;
		case 5: // 101  NAND
			return (bool)~(exec(*((node *)(root.a))) & exec(*((node *)(root.b))));
			break;
		case 6: // 110  NOR
			return (bool)~(exec(*((node *)(root.a))) | exec(*((node *)(root.b))));
			break;
		case 7: // 111  XNOR
			return (bool)~(exec(*((node *)(root.a))) ^ exec(*((node *)(root.b))));
			break;
		default:
			return false;
			break;
	}
}

int fitness(const std::vector<node *> &root,
			std::deque<bool> & input,
			const std::vector< std::vector<bool> > &output,
			const std::set<weighted_pointer> & gate,
			std::vector<bool> & perfect){
				
	int solution = 0;
	for_each(gate.begin(),gate.end(),[](weighted_pointer const & w){w.weight = 0;});
	std::fill(perfect.begin(),perfect.end(),true);
	for(int i = 0; i < (1 << input.size()); i++){
		for(size_t j = 0; j < input.size(); j++)
			input[j] = ((i >> j) & 1);
		for(size_t j = 0; j < root.size(); j++){
			if(exec(*(root[j])) == output[j][i])
				solution += 100;
			else
				perfect[j] = false;
		}	
	}
	for(auto &&item_perfect : perfect)
		if(item_perfect)
			solution += 100;
	
	return solution - gate.size() + input.size();
}
