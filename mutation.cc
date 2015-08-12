#include "mutation.h"

void changeRoots(std::vector<node *> &root, std::set<weighted_pointer> & gate){
	for(unsigned int i = 0; i < root.size(); i++){
		auto it = std::find_if(gate.begin(),gate.end(),[&](const weighted_pointer & tmp){return tmp.pointer.get() == root[i];});
		if(it->weight == 0 && (rand() % 2)){
			node * actualRoot = root[i];
			std::set<weighted_pointer>::iterator at;
			do{
				at = next(gate.begin(),rand() % gate.size());
			}while(actualRoot == at->pointer.get());
			root[i] = at->pointer.get();
		}
	}
}

void tryAdd(std::set<weighted_pointer> & gate){
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

void tryRemove(std::set<weighted_pointer> & gate, std::deque<bool> & input,std::vector<node *> root){
	if(gate.size() <= input.size())
		return;
	std::set<weighted_pointer>::iterator at;
	do{
		at = std::next(gate.begin(),rand() % gate.size());
	}while((at->pointer)->oper == 0);
	if(at->weight > 0)
		return;
	
	//cout << "AFTER CC" << endl;
	
	node * tmp = at->pointer.get();
	
	//cout << "AFTER GG" << endl;
	
	for (auto it=gate.begin(); it != gate.end(); ++it){
		if((node *)(it->pointer)->a == tmp){
    		(it->pointer)->a = tmp -> a;
		}
    	if((it->pointer)->oper != 4){
    		if((node *)(it->pointer)->b == tmp)
    			(it->pointer)->b = tmp -> a;
    	}
	}
	
	//cout << "AFTER EE" << endl;
	
	for(auto it=root.begin(); it != root.end(); ++it){
    	if((*it) == tmp){
    		*it = (node*)(tmp -> a);
		}
	}
	
	gate.erase(at);
	
	//cout << "AFTER DD" << endl;
	//delete tmp;
}

void randomize(std::set<weighted_pointer> & gate,std::deque<bool> & input,std::vector<node*> & root){
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
