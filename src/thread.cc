#include "thread.h"
#include <fstream>

/** @page thread
 * This page contains the work for every thread.
 *  
*/

/** Prints the actual output of the circuit and the desired one
 *
 * @param[out] best_gate Highest fitness circuit found
 * @param[out] best_root The output gates from the highest fitness circuit found
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 */
void thread_work(std::vector<node> &best_gate, std::vector<size_t> &best_root, size_t & input_lenght,std::vector< std::vector<bool> > & output){
	
	std::vector<node> gate;
	std::vector<size_t> root;
	
	gate.assign(best_gate.begin(),best_gate.end());
	root.assign(best_root.begin(),best_root.end());
	
	// SHOULD BE GLOBAL?
	int g_num_genes = 10;
	
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
