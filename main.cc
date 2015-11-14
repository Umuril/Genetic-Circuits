/**
 * @mainpage Genetic Circuits
 *
 * The main objective is to find the optimal combinational circuit given n inputs and the desired output. <br/>
 * To do so, I decided to use a Genetic Algorithm.	
 * 
 * Logical Steps:<br />
 * 	Firstly, I generate a circuit which every output is taken from first input. Then I create many "fake" gates
 * 	as much the number of input, this is set an end to the circuit. The ::gate vector contains a vector of nodes,
 * 	every node is a logic binary gate with has a type, and the reference to the gates that's connected to. Then I 
 * 	create different threads where each one modifies the actual best solution to find a better one.
 * 
 * Data structure:
 * - std::deque<bool> input
 *  	+ used to generate all possible inputs
 * - std::vector< std::vector<bool> > output
 * 	+ it contains the desired outputs
 * - std::vector<size_t> root 
 * 	+ it contains the index of the gates which will be taken to get the desired output
 * - std::vector<node> gate 
 * 	+ Contains all the circuit information
 * 
 * @author Eduard Rubio Cholbi
 */

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

/** Main function
 *
 * There're 2 task the main function does.
 * 
 * 1) Initializes the variables and sets up what's needed to do a multi-threading work.
 * 2) Executes the loop where the thread will be called to find better solutions.
 * 
 */

int main(){
	srand(time(NULL));
	size_t input_lenght; ///< we just need the lenght of the deque in order to generate it every time.
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
