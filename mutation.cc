#include "mutation.h"

void changeRoots(	std::vector<node *> &root,
					std::set<weighted_pointer> &gate){
						
	for(size_t i = 0; i < root.size(); i++){
		auto it = std::find_if(gate.begin(),gate.end(),[&](const weighted_pointer & tmp){return tmp.pointer.get() == root[i];});
		if(it->weight == 0 && (rand() % 2)){
			node * actualRoot = root[i];
			std::set<weighted_pointer>::iterator at;
			do
				at = next(gate.begin(),rand() % gate.size());
			while(actualRoot == at->pointer.get());
			root[i] = at->pointer.get();
		}
	}
}

void randomize(	std::set<weighted_pointer> &gate,
				std::deque<bool> &input,
				std::vector<node *> &root){
	
	unsigned short int random;
	random = rand() % 100;
	if(random <= 90)
		tryAdd(gate);
	else
		tryRemove(gate,input,root);
	if(random <= 100)
		changeRoots(root,gate);
	return;	
}

void tryAdd(std::set<weighted_pointer> &gate){
	weighted_pointer addpointer;
	int random = rand() % 7 + 1;
	int randomA = rand() % gate.size();
	auto A = gate.begin();
	std::advance(A,randomA);
	if(random == 4){
		addpointer.pointer = std::make_unique<node>(node{(unsigned int)random,A->pointer.get(),nullptr});
	}else{
		int randomB;
		do
			randomB = rand() % gate.size();
		while(randomA == randomB);
		auto B = gate.begin();
		advance(B,randomB);
		addpointer.pointer = std::make_unique<node>(node{(unsigned int)random,A->pointer.get(),B->pointer.get()});
	}
	addpointer.weight = 1;
	gate.emplace(std::move(addpointer));
	return;
}

void tryRemove(	std::set<weighted_pointer> &gate,
				std::deque<bool> &input,
				std::vector<node *> &root){
					
	if(gate.size() <= input.size())
		return;
	std::set<weighted_pointer>::iterator at;
	do
		at = std::next(gate.begin(),rand() % gate.size());
	while((at->pointer)->oper == 0);
	if(at->weight > 0)
		return;
	
	node * tmp_pointer = at->pointer.get();
	
	for (auto it = gate.begin(); it != gate.end(); ++it){
		if((node *)(it->pointer)->a == tmp_pointer)
    		(it->pointer)->a = tmp_pointer -> a;
    	if((it->pointer)->oper != 4)
    		if((node *)(it->pointer)->b == tmp_pointer)
    			(it->pointer)->b = tmp_pointer -> a;
	}
	
	for(auto it = root.begin(); it != root.end(); ++it)
    	if((*it) == tmp_pointer)
    		*it = (node*)(tmp_pointer -> a);
	
	gate.erase(at);
}
