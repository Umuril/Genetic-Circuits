#ifndef STRUCTS_H
#define STRUCTS_H

struct node {
	unsigned int oper : 3;
	size_t a;
	size_t b;
};

struct Params {
	std::vector<node> gate;
	std::vector<size_t> root;
	size_t input_lenght;
	std::vector< std::vector<bool> > output;
	unsigned int best_fitness;
	unsigned int generation;
};

#endif
