#include "mutation.h"
#include "debug.h"
#include <iostream>

void changeRoots(	std::vector<node *> &root,
					std::set<weighted_pointer> &gate){
	
	for(auto &&item_root : root){
		auto it = std::find_if(gate.begin(),gate.end(),[&](const weighted_pointer & tmp){return tmp.pointer.get() == item_root;});
		if(it->weight == 0 && (rand() % 2)){
			node * actualRoot = item_root;
			std::set<weighted_pointer>::iterator at;
			do
				at = next(gate.begin(),rand() % gate.size());
			while(actualRoot == at->pointer.get());
			item_root = at->pointer.get();
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
	addpointer.weight = 0;
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
	
	for(auto &&item_gate : gate){
		if((node *)(item_gate.pointer)->a == tmp_pointer)
    		item_gate.pointer->a = tmp_pointer -> a;
    	if((item_gate.pointer)->oper != 4)
    		if((node *)(item_gate.pointer)->b == tmp_pointer)
    			item_gate.pointer->b = tmp_pointer -> a;
	}
	
	for(auto &&item_root : root)
    	if(item_root == tmp_pointer)
    		item_root = (node*)(tmp_pointer -> a);
	
	gate.erase(at);
}
