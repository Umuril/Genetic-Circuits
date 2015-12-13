#include "debug.h"

/** @page debug
 * This page contains all debug functions.
 *  
*/

/** Prints the actual output of the circuit and the desired one
 *
 * @param[out] os ostream to print
 * @param[in] gate Circuit information
 * @param[in] root Output gates
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 */
void print(std::ostream & os, const std::vector<node> & gate,
			const std::vector<size_t> & root, const size_t & input_lenght, 
			const std::vector< std::vector<bool> > &output){
	std::deque<bool> input(input_lenght);
	for(int i = 0; i < (1 << input.size()); i++){
		for(size_t j = 0; j < input.size(); j++)
			input[j] = ((i >> j) & 1);
		for(auto &&item_input : input)
			os << item_input;
		for(int j = output.size() - 1; j >= 0; j--){
			os << " O: " << output[j][i];
			os << " I: " << exec(gate[root[j]],input,gate);
		}
		os << '\n';
	}
}

/** Calls all debug functions
 *
 * @param[out] os ostream to print
 * @param[in] gate Circuit information
 * @param[in] root Output gates
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 */
void printData(std::ostream & os, const std::vector<node> & gate,
				const std::vector<size_t> & root, const size_t & input_lenght,
				const std::vector< std::vector<bool> > & output){
	os << "BEST FITNESS: " << fitness(gate,root,input_lenght,output) << '\n';
	print(os,gate,root,input_lenght,output);
	printRoot(os,root);	
	printGate(os,gate);
}

/** Prints all the circuit information
 *
 * @param[out] os ostream to print
 * @param[in] gate Circuit information
 */
void printGate(std::ostream & os, const std::vector<node> & gate){
	for(auto &&item_gate : gate)
		os << "(" << item_gate.oper << "," << item_gate.a << "," << item_gate.b << ") ";
	os << std::endl;
	return;
}

/** Prints the output gates
 *
 * @param[out] os ostream to print
 * @param[in] root Output gates
 */
void printRoot(std::ostream & os, const std::vector<size_t> & root){
	for (auto it=root.rbegin(); it != root.rend(); ++it)
    	os << " ROOT:  " << *it;
	os << '\n';
}
