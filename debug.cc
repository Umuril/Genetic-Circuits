#include "debug.h"

/** @page debug
 * This page contains all debug functions.
 *  
*/

/** Prints the actual output of the circuit and the desired one
 *
 * @param[in] gate Circuit information
 * @param[in] root Output gates
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 */
void print(std::vector<node> &gate, std::vector<size_t> &root,const size_t &input_lenght,const std::vector< std::vector<bool> > &output){
	std::deque<bool> input(input_lenght);
	for(int i = 0; i < (1 << input.size()); i++){
		for(size_t j = 0; j < input.size(); j++)
			input[j] = ((i >> j) & 1);
		for(auto &&item_input : input)
			std::cout << item_input;
		for(int j = output.size() - 1; j >= 0; j--){
			std::cout << " O: " << output[j][i];
			std::cout << " I: " << exec(gate[root[j]],input,gate);
		}
		std::cout << '\n';
	}
}

/** Calls all debug functions
 *
 * @param[in] gate Circuit information
 * @param[in] root Output gates
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 */
void printData(std::vector<node> &gate, std::vector<size_t> &root,const size_t & input_lenght,const std::vector< std::vector<bool> > &output){
	std::cout << "BEST FITNESS: " << fitness(gate,root,input_lenght,output) << '\n';
	print(gate,root,input_lenght,output);
	printRoot(root);	
	printGate(gate);
}

/** Prints the output gates
 *
 * @param[in] root Output gates
 */
void printRoot(const std::vector<size_t> &root){
	for (auto it=root.rbegin(); it != root.rend(); ++it)
    	std::cout << " ROOT:  " << *it;
	std::cout << '\n';
}

/** Prints all the circuit information
 *
 * @param[in] gate Circuit information
 */
void printGate(const std::vector<node> &gate){
	for(auto &&item_gate : gate)
		std::cout << "(" << item_gate.oper << "," << item_gate.a << "," << item_gate.b << ") ";
	std::cout << std::endl;
	return;
}
