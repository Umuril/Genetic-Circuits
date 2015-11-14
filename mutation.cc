#include "mutation.h"
#include "debug.h"
#include <iostream>

void changeRoots(std::vector<node> &gate, std::vector<size_t> &root){
    for(auto &&item_root : root){
        size_t new_root;
        do
            new_root = rand() % gate.size();
        while(item_root == new_root);
        item_root = new_root;
    }
}

void randomize(std::vector<node> &gate, std::vector<size_t> &root, const size_t &input_lenght){

	unsigned short int random;
	random = rand() % 100;

	if(random <= 75){
        //std::cout << "ADD: ";
		//printGate(gate);
		tryAdd(gate,input_lenght);
	}else{
        //std::cout << "REMOVE: ";
		//printGate(gate);
		tryRemove(gate,input_lenght,root);
	}
	if(random <= 100)
		changeRoots(gate,root);
	return;
}

void tryAdd(std::vector<node> &gate, const size_t & input_lenght){
    int random = rand() % 7 + 1;
    int randomA = rand() % gate.size();
    int randomB = rand() % gate.size();
    gate.emplace_back(node{random,randomA,randomB});
	return;
}

void tryRemove(std::vector<node> &gate, const size_t & input_lenght, std::vector<size_t> &root){

	if(gate.size() <= input_lenght)
		return;

    size_t pt = (rand() % (gate.size()-input_lenght))+input_lenght;

    //printGate(gate);
    //std::cout << "PT: " << pt;

    for(int i = input_lenght; i < gate.size(); i++){
        if(gate[i].a >= pt)
            gate[i].a--;
        if(gate[i].b >= pt)
            gate[i].b--;
    }


    gate.erase(gate.begin()+pt);

    //std::cout << " - AFTER    ";
    //printGate(gate);
}

