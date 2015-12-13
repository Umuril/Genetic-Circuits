#include "mutation.h"


/** @page mutation
 * This page contains all possible modifications to the circuit.
 *  
*/

/** This function try to find a better solution given a good one
 *
 * @param[out] best_gate Highest fitness circuit found
 * @param[out] best_root The output gates from the highest fitness circuit found
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 */
void evolve(std::vector<node> & best_gate,
				std::vector<size_t> & best_root,
				const size_t & input_lenght,
				const std::vector< std::vector<bool> > & output){

	std::vector<node> gate;
	std::vector<size_t> root;

	gate.assign(best_gate.begin(),best_gate.end());
	root.assign(best_root.begin(),best_root.end());

	int g_num_genes = 10; ///< I found 10 to solve most of my problems in a good time

	int new_fitness = 0;
	int best_fitness = fitness(best_gate,best_root,input_lenght,output);

	for(int i = 0; i < g_num_genes; i++){
		randomize(gate,root,input_lenght,output);
		new_fitness = fitness(gate,root,input_lenght,output);
		if(new_fitness >= best_fitness){
			best_gate.assign(gate.begin(),gate.end());
			best_root.assign(root.begin(),root.end());
			return;
		}
	}
}

/** Changes all root values
 *
 * @param[in]	gate Circuit information
 * @param[in,out] root Output gates
 */
void changeRoots(const std::vector<node> & gate, std::vector<size_t> & root){
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
 * @param[in] output Output desired
 */
void randomize(std::vector<node> & gate, std::vector<size_t> & root,
			const size_t &input_lenght,const std::vector< std::vector<bool> > & output){

	unsigned short int random;
	random = rand() % 100;
	unsigned int actual_fitness = fitness(gate,root,input_lenght,output);
	unsigned int optimal_fitness = output.size()*(1<<input_lenght)*100;
	
	if(actual_fitness > optimal_fitness-100)
		tryRemove(gate,input_lenght,root);
	
	tryModify(gate,input_lenght,root);
	if(gate.size() < 40 && random < 50 && actual_fitness <= optimal_fitness-100){
        tryAdd(gate,input_lenght);
	}
	return;
}

/** Adds one logic gate at the end of the circuit
 *
 * @param[in,out] gate Circuit information
 * @param[in] input_lenght Number of inputs
 */
void tryAdd(std::vector<node> & gate, const size_t & input_lenght){
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
void tryRemove(std::vector<node> &gate, const size_t & input_lenght,
				std::vector<size_t> & root){

	if(gate.size() <= input_lenght)
		return;

    size_t pt = (rand() % (gate.size()-input_lenght))+input_lenght;

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
}

/** Modifies (if possible) one logic gate from the circuit
 *
 * @param[in,out] gate Circuit information
 * @param[in] input_lenght Number of inputs
 * @param[in] root Output gates
 */
void tryModify(std::vector<node> &gate, const size_t & input_lenght,
				std::vector<size_t> &root){
	
	if(gate.size() <= input_lenght)
		return;
	
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
		unsigned int random = rand() % 3; 
		switch(random){
			case 0:
				gate[pt].oper = rand() % 7 + 1;
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
