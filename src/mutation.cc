#include "mutation.h"
#include "debug.h"
#include <iostream>

/** @page mutation
 * This page contains all possible modifications to the circuit.
 *  
*/

/** Changes all root values
 *
 * @param[in]	gate Circuit information
 * @param[in,out] root Output gates
 */
void changeRoots(std::vector<node> &gate, std::vector<size_t> &root){
    for(auto &&item_root : root){
        size_t new_root;
        do
            new_root = rand() % gate.size();
        while(item_root == new_root);
        item_root = new_root;
    }
}

/** Chooses what kind of modifications will be done
 *
 * @param[in] gate Circuit information
 * @param[in] root Output gates
 * @param[in] input_lenght Number of inputs
 */
void randomize(std::vector<node> &gate, std::vector<size_t> &root, const size_t &input_lenght,std::vector< std::vector<bool> > & output){

	unsigned short int random;
	random = rand() % 100;
	
	if(fitness(gate,root,input_lenght,output) > output.size()*(1<<input_lenght)*100-100)
		tryRemove(gate,input_lenght,root);
	
	tryModify(gate,input_lenght,root);
	//if(random <= 50){
	if(gate.size() < 40 && random <= 50){
        //std::cout << "ADD: ";
		//printGate(gate);
		tryAdd(gate,input_lenght);
	}/*else{
        //std::cout << "REMOVE: ";
		//printGate(gate);
		tryRemove(gate,input_lenght,root);
	}*/
	//changeRoots(gate,root);
	return;
}

/** Adds one logic gate at the end of the circuit
 *
 * @param[in,out] gate Circuit information
 * @param[in] input_lenght Number of inputs
 */
void tryAdd(std::vector<node> &gate, const size_t & input_lenght){
    unsigned int random = rand() % 7 + 1;
    size_t randomA = rand() % gate.size();
    size_t randomB = rand() % gate.size();
    gate.emplace_back(node{random,randomA,randomB});
    return;
}

/** Removes (if possible) one logic gate from the circuit
 *
 * @param[in,out] gate Circuit information
 * @param[in] input_lenght Number of inputs
 */
void tryRemove(std::vector<node> &gate, const size_t & input_lenght, std::vector<size_t> &root){

	if(gate.size() <= input_lenght)
		return;

    size_t pt = (rand() % (gate.size()-input_lenght))+input_lenght;

    //printGate(gate);
    //std::cout << "PT: " << pt;

    for(size_t i = input_lenght; i < gate.size(); i++){
        if(gate[i].a >= pt)
            gate[i].a--;
        if(gate[i].b >= pt)
            gate[i].b--;
    }
	
	for(size_t i = 0; i < root.size(); i++){
		if(root[i] >= pt)
            root[i]--;
	}
    gate.erase(gate.begin()+pt);

    //std::cout << " - AFTER    ";
    //printGate(gate);
}

void tryModify(std::vector<node> &gate, const size_t & input_lenght, std::vector<size_t> &root){
	
	if(gate.size() <= input_lenght){
		return;
	}

    size_t pt = (rand() % (gate.size()+root.size()-input_lenght))+input_lenght;
	
	if(pt >= gate.size()){
		unsigned int random = pt - gate.size();
    	size_t new_root = rand() % root.size();
	    do
	        new_root = rand() % gate.size();
	    while(root[random] == new_root);
	    root[random] = new_root;
	    return;
	} else {
		//std::cout << "ESCI" << pt << std::endl;
		unsigned int random = rand() % 3; 
		switch(random){
			case 0:
				gate[pt].oper = rand() % 7 + 1;
				//std::cout << "SCI: " << gate[pt].oper << std::endl;
				break;
			case 1:
				gate[pt].a = rand() % pt;
				break;
			case 2:
				gate[pt].b = rand() % pt;
				break;
    	}
    }
}
