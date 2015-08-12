#include "init.h"

const char *FILENAME = "data.txt";

bool read_output_from_file(std::vector< std::vector<bool> > &output, size_t &input_lenght){
	std::ifstream ifile(FILENAME);
	if(!ifile)
		return false;
	int output_lenght;
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

void init(std::deque<bool> &input, const std::vector< std::vector<bool> > &output, std::set<weighted_pointer> &gate, std::vector<node *> &root){
	srand(time(NULL));
	
	for(size_t i = 0; i < input.size(); i++){
		gate.insert(std::move(weighted_pointer{1,std::make_unique<node>(node{0,&input[i],nullptr})}));
	}
	
	//gate.insert(move(weighted_pointer{1,make_unique<node>(new node{0,&input[0],nullptr})}));
	node *copy_pointer = gate.begin()->pointer.get();
	
	for(size_t i = 0; i < output.size(); i++){
		root.push_back(copy_pointer);
	}
	
}
