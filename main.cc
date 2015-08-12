#include <chrono>
#include <iostream>
#include <vector>
#include "init.h"
#include "structs.h"

int main(){
	srand(time(NULL));
	
	std::vector< std::vector<bool> > output; 
	if(!read_output_from_file(output))
		return 1;
	
	return 0;
}
