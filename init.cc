#include "init.h"

void init(	std::deque<bool> &input,
			const std::vector< std::vector<bool> > &output,
			std::set<weighted_pointer> &gate,
			std::vector<node *> &root){
				
	for(auto &&item_input : input)
		gate.insert(std::move(weighted_pointer{1,std::make_unique<node>(node{0,&item_input,nullptr})}));
	
	node *tmp_pointer = gate.begin()->pointer.get();
	
	for(auto &&dummy : output)
		root.push_back(tmp_pointer);
}

bool read_output_from_file(	std::vector< std::vector<bool> > &output,
							size_t &input_lenght){
								
	const char *FILENAME = "data.txt";
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
