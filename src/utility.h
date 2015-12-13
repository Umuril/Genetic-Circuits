#ifndef UTILITY_H
#define UTILITY_H

#include <deque>
#include <fstream>
#include <vector>
#include <iostream>
#include "structs.h"

bool read_output_from_file(const char * filename,
		std::vector< std::vector<bool> > &output, size_t &input_lenght);
bool exec(const node root, const std::deque<bool> & input, const std::vector<node> & gate);
unsigned int fitness(const std::vector<node> &gate, const std::vector<size_t> &root,
		const size_t &input_lenght,const std::vector< std::vector<bool> > &output);

#endif
