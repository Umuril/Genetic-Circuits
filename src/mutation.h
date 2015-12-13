#ifndef MUTATION_H
#define MUTATION_H

#include <deque>
#include <iostream>
#include <vector>
#include "structs.h"
#include "debug.h"

void evolve(std::vector<node> & best_gate,
				std::vector<size_t> & best_root,
				const size_t & input_lenght,
				const std::vector< std::vector<bool> > & output);
void changeRoots(const std::vector<node> & gate, std::vector<size_t> & root);
void randomize(std::vector<node> & gate, std::vector<size_t> & root,
			const size_t &input_lenght,const std::vector< std::vector<bool> > & output);
void tryAdd(std::vector<node> & gate, const size_t & input_lenght);
void tryRemove(std::vector<node> &gate, const size_t & input_lenght,
				std::vector<size_t> & root);
void tryModify(std::vector<node> &gate, const size_t & input_lenght,
				std::vector<size_t> &root);

#endif
