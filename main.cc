#include <chrono>
#include <deque>
#include <iostream>
#include <set>
#include <vector>
#include "debug.h"
#include "utility.h"
#include "init.h"
#include "structs.h"

int main(){
	srand(time(NULL));
	size_t input_lenght;
	std::vector< std::vector<bool> > output; 
	if(!read_output_from_file(output,input_lenght))
		return 1;
	
	std::vector<node *> root(output.size());
	std::deque<bool> input(input_lenght);
	std::set<weighted_pointer> gate;
	std::vector<bool> perfect(output.size());
	
	init(input,output,gate,root);
	
	return 0;
}
