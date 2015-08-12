#ifndef MUTATION_H
#define MUTATION_H

#include <deque>		// std::deque
#include <set>			// std::set
#include <vector>		// std::vector
#include "structs.h"	// struct node, struct weighted_pointer

void changeRoots(	std::vector<node *> &root,
					std::set<weighted_pointer> &gate);
void randomize(	std::set<weighted_pointer> &gate,
				std::deque<bool> &input,
				std::vector<node *> &root);
void tryAdd(std::set<weighted_pointer> &gate);
void tryRemove(	std::set<weighted_pointer> &gate,
				std::deque<bool> &input,
				std::vector<node *> &root);

#endif
