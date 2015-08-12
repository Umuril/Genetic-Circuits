#include "init.h"

const char *FILENAME = "data.txt";

bool read_output_from_file(std::vector< std::vector<bool> > &output){
	std::ifstream ifile(FILENAME);
	if(!ifile)
		return false;
	int input_lenght, output_lenght;
	ifile >> input_lenght;
	ifile >> output_lenght;
	output.resize(output_lenght,std::vector<bool>(1<<input_lenght));
	char c;
	for(int i = 0; i < output_lenght; i++)
		for(int j = 0; j < (1<<input_lenght); j++){
			ifile.get(c);
			output[i][j] = (c=='1')?true:false;
		}
	return true;		
}
