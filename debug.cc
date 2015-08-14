#include "debug.h"

void print(	std::deque<bool> &input,
			const std::vector< std::vector<bool> > &output,
			const std::vector<node *> &root){
				
	for(int i = 0; i < (1 << input.size()); i++){
		for(size_t j = 0; j < input.size(); j++)
			input[j] = ((i >> j) & 1);
		for(auto &&item_input : input)
			std::cout << item_input;
		for(int j = output.size() - 1; j >= 0; j--)
			std::cout << " I: " << exec(*(root[j])) << " O: " << output[j][i];
		std::cout << '\n';
	}
}

void printData(	std::deque<bool> &input,
				const std::vector< std::vector<bool> > &output,
				const std::vector<node *> &root,
				const std::set<weighted_pointer> &gate,
				std::vector<bool> &perfect){
					
	std::cout << "BEST FITNESS: " << fitness(root,input,output,gate,perfect) << '\n';
	print(input,output,root);

	for (auto it=input.rbegin(); it != input.rend(); ++it)
    	std::cout << " INPUT: " << &(*it);
    std::cout << '\n';
    
	for (auto it=root.rbegin(); it != root.rend(); ++it)
    	std::cout << " ROOT:  " << *it;
	std::cout << '\n';
			
	for(auto &&item_gate : gate)
    	std::cout << "gate: " << item_gate.pointer.get() << " w:" << item_gate.weight << ' ' << item_gate.pointer->oper << ' ' << item_gate.pointer->a << ' ' << item_gate.pointer->b << '\n';
}

void printRoots(const node *root){
	if(!root)
		return;
	std::cout << root << ": " << root-> oper << ' ' << root->a << ' ' << root->b << '\n';
	if(root->oper == 0)
		return;
	printRoots((node *)root->a);
	printRoots((node *)root->b);	
}
