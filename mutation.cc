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
	changeRoots(gate,root);
	return;
}

/** Adds one logic gate at the end of the circuit
 *
 * @param[in,out] gate Circuit information
 * @param[in] input_lenght Number of inputs
 */
void tryAdd(std::vector<node> &gate, const size_t & input_lenght){
    int random = rand() % 7 + 1;
    int randomA = rand() % gate.size();
    int randomB = rand() % gate.size();
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

