#include "thread.h"
#include <fstream>

std::mutex mtx;

void thread_work(std::vector<node> &best_gate, std::vector<size_t> &best_root, size_t & input_lenght,std::vector< std::vector<bool> > & output){
	
	srand(time(NULL));
	std::vector<node> gate;
	std::vector<size_t> root;
	
	gate.assign(best_gate.begin(),best_gate.end());
	root.assign(best_root.begin(),best_root.end());
	
	std::ofstream ofile("gates.txt",std::ofstream::app);
	
	// SHOULD BE GLOBAL
	int g_num_genes = 10;
	
	int new_fitness = 0;
	int best_fitness = fitness(best_gate,best_root,input_lenght,output);
	
	for(int i = 0; i < g_num_genes; i++){
		
		randomize(gate,root,input_lenght);
		new_fitness = fitness(gate,root,input_lenght,output);
		if(new_fitness > best_fitness){
			mtx.lock();
			
			best_gate.assign(gate.begin(),gate.end());
			best_root.assign(root.begin(),root.end());
			mtx.unlock();
			
		}
	}
	ofile.close();
}
