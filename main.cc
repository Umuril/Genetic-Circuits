#include <chrono>
#include <deque>
#include <iostream>
#include <set>
#include <vector>
#include "debug.h"
#include "utility.h"
#include "mutation.h"
#include "init.h"
#include "structs.h"

int main(){
	srand(time(NULL));
	size_t input_lenght;
	std::vector< std::vector<bool> > output; 
	if(!read_output_from_file(output,input_lenght))
		return 1;
	
	std::vector<node *> root;
	std::deque<bool> input(input_lenght);
	std::set<weighted_pointer> gate;
	std::vector<bool> perfect(output.size());
	
	init(input,output,gate,root);
	fitness(root,input,output,gate,perfect);
	printData(input,output,root,gate,perfect);
	int bestfitness = 0;
	int newone = 0;
	double media = 0;
	unsigned long long int nums = 0;
	backup bestsolution;
	bestsolution.gate.insert(gate.begin(),gate.end());
	bestsolution.root.assign(root.begin(),root.end());
	do{
		randomize(gate,input,root);
		for_each(gate.begin(),gate.end(),[](weighted_pointer const & w){w.weight = 0;});
		newone = fitness(root,input,output,gate,perfect);
		//if(newone > 2000)
		media = ((media*nums)+newone)/(nums+1);
		//if(nums < 100)
		//	nums++;
		printf("fitness: %7d media: %7.2f gate_size: %5d nums: %llu\r",newone,media,gate.size(),nums);
		if(newone < bestfitness-1000){
			nums++;
			gate.clear();
			gate.insert(bestsolution.gate.begin(),bestsolution.gate.end());
			root.assign(bestsolution.root.begin(),bestsolution.root.end());
		}
		if(newone > bestfitness){
			bestsolution.gate.clear();
			bestsolution.gate.insert(gate.begin(),gate.end());
			bestsolution.root.assign(root.begin(),root.end());
			bestfitness = newone;
		//}
			system("cls");
			
			for(unsigned int i = 0; i < root.size(); i++){
				if(perfect[i])
					addWeight(root[i],true,gate);
				std::cout << " " << perfect[i];
			}
			std::cout << "\n";
			printData(input,output,root,gate,perfect);
		}
		//std::this_thread::sleep_for(std::chrono::milliseconds(5000));
	}while(bestfitness < 30000);
	
	return 0;
}
