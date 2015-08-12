#ifndef INIT_H
#define INIT_H

#include <deque>		// std::deque
#include <fstream>		// std::ifstream
#include <vector>		// std::vector, std::vector<bool>
#include "structs.h"	// struct node, struct weighted_pointer

void init(	std::deque<bool> &input,
			const std::vector< std::vector<bool> > &output,
			std::set<weighted_pointer> &gate,
			std::vector<node *> &root);
bool read_output_from_file(	std::vector< std::vector<bool> > &output,
							size_t &input_lenght);

#endif
