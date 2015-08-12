#include <chrono>
#include <iostream>
#include <vector>
#include "init.h"
#include "structs.h"

int main(){
	srand(time(NULL));
	
	vector<vector<bool>> output; 
	if(!read_data_from_file(output))
		return -1;
	
	return 0;	
}
