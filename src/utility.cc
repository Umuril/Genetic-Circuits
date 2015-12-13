#include "utility.h"

/** @page utility
 * This page contains all utility functions.
 *  
*/

/** Loads output matrix from file
 *
 * @param[in] filename path of file
 * @param[out] output Output desired
 * @param[in] input_lenght Number of inputs
 * @return Flag that returns if the file could be opened.
 */
bool read_output_from_file(const char * filename,
		std::vector< std::vector<bool> > &output, size_t &input_lenght){
	std::ifstream ifile(filename);
	if(!ifile)
		return false;
	int output_lenght;
	ifile >> input_lenght;
	ifile >> output_lenght;
	output.resize(output_lenght,std::vector<bool>(1<<input_lenght));
	char c;
	ifile.get(c);
	ifile.get(c);
	for(int i = 0; i < output_lenght; i++){

		for(int j = 0; j < (1<<input_lenght); j++){
			ifile.get(c);
			output[i][j] = (c=='1')?true:false;
		}
		ifile.get(c);
		ifile.get(c);
	}
	return true;
}

/** Executes recursively the output of a gate
 *
 * @param[in] root Gate from the output will be calculated from
 * @param[in] input The input given to the circuit
 * @param[in] gate The circuit informations
 * @return The output after the execution
 */
bool exec(const node root, const std::deque<bool> & input, const std::vector<node> & gate){
	switch(root.oper){
		case 0: // 000  NOTHING
			return input[root.a];
			break;
		case 1: // 001  AND
			return exec(gate[root.a],input,gate) & exec(gate[root.b],input,gate);
			break;
		case 2: // 010  OR
			return exec(gate[root.a],input,gate) | exec(gate[root.b],input,gate);
			break;
		case 3: // 011  XOR
			return exec(gate[root.a],input,gate) ^ exec(gate[root.b],input,gate);
			break;
		case 4: // 100  NOT
			return ~exec(gate[root.a],input,gate);
			break;
		case 5: // 101  NAND
			return ~(exec(gate[root.a],input,gate) & exec(gate[root.b],input,gate));
			break;
		case 6: // 110  NOR
			return ~(exec(gate[root.a],input,gate) | exec(gate[root.b],input,gate));
			break;
		case 7: // 111  XNOR
			return ~(exec(gate[root.a],input,gate) ^ exec(gate[root.b],input,gate));
			break;
		default:
			return false;
			break;
	}
}


/** Fitness function
 *
 * @param[in] gate Circuit information
 * @param[in] root Output gates
 * @param[in] input_lenght Number of inputs
 * @param[in] output Output desired
 * @return Fitness value of actual circuit
 */
unsigned int fitness(const std::vector<node> &gate, const std::vector<size_t> &root,
		const size_t &input_lenght,const std::vector< std::vector<bool> > &output){
	std::deque<bool> input(input_lenght);
	unsigned int solution = 0;
	
	for(int i = 0; i < (1 << input.size()); i++){
		for(size_t j = 0; j < input.size(); j++)
			input[j] = ((i >> j) & 1);
		for(size_t j = 0; j < root.size(); j++)
			if(exec(gate[root[j]],input,gate) == output[j][i])
				solution += 100;
	}
	
	return solution - gate.size() + input_lenght;
}
