#include "init.h"

/** @page init
 * This page contains all the initialacion functions.
 *  
*/

/** Prints the actual output of the circuit and the desired one
 *
 * @param[out] root Output gates
 * @param[in] input_lenght Number of inputs
 * @return Flag that returns if the file could be opened.
 */
bool read_output_from_file(	std::vector< std::vector<bool> > &output, size_t &input_lenght){
								
	const char *FILENAME = "data.txt";
	std::ifstream ifile(FILENAME);
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
