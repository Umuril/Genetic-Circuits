#ifndef MUTATION_H
#define MUTATION_H

#include <algorithm>	// std::find_if
#include <deque>		// std::deque
#include <set>			// std::set
#include <vector>		// std::vector
#include "structs.h"	// struct node, struct weighted_pointer

void changeRoots(std::vector<node> &gate, std::vector<size_t> &root);
void randomize(std::vector<node> &gate, std::vector<size_t> &root, const size_t &input_lenght);
void tryAdd(std::vector<node> &gate, const size_t & input_lenght);
void tryRemove(std::vector<node> &gate, const size_t &input_lenght, std::vector<size_t> &root);
void tryMutate(std::vector<node> &gate, const size_t &input_lenght);
void tryAddFirst(std::vector<node> &gate, const size_t &input_lenght);

#endif
