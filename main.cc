#include <chrono>
#include <deque>
#include <iostream>
#include <set>
#include <thread>
#include <vector>
#include "thread.h"
#include "debug.h"
#include "utility.h"
#include "mutation.h"
#include "init.h"
#include "structs.h"

using namespace std;

int main(){
	srand(time(NULL));
	size_t input_lenght;
	std::vector< std::vector<bool> > output; 
	if(!read_output_from_file(output,input_lenght))
		return 1;
	
	std::vector<std::thread> threads;
	
	unsigned int best_fitness = 0;
	std::vector<size_t> root(output.size(),0);
	std::vector<node> gate;
	
	for(int i = 0; i < input_lenght; i++)
		gate.emplace_back(node{0,i,0});
	
	printData(gate,root,input_lenght,output);
	unsigned int generation = 0;
	do{
		for(unsigned int i = 0; i < std::thread::hardware_concurrency(); i++)
			threads.push_back(std::thread(thread_work,std::ref(gate),std::ref(root),std::ref(input_lenght),std::ref(output)));
		for (auto& th : threads)
			th.join();
		threads.clear();
		if(fitness(gate,root,input_lenght,output) > best_fitness){
			best_fitness = fitness(gate,root,input_lenght,output);
			system("clear");
			printData(gate,root,input_lenght,output);
			std::cout << "Generation: " << generation << " Best fitness: " << best_fitness << std::endl;
		}
		generation++;
	}while(best_fitness < output.size()*(1<<input_lenght)*100-50);
	
	return 0;
}
