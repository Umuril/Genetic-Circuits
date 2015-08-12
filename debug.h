#ifndef DEBUG_H
#define DEBUG_H

#include <deque>		// std::deque
#include <iostream>		// std::cout
#include <vector>		// std::vector,std::vector<bool>
#include "structs.h"	// struct node
#include "utility.h"	// exec(), fitness()

void print(	std::deque<bool> & input,
			const std::vector< std::vector<bool> > & output,
			const std::vector<node *> & root);
void printData(	std::deque<bool> & input,
				const std::vector< std::vector<bool> > & output,
				const std::vector<node *> & root,
				const std::set<weighted_pointer> & gate,
				std::vector<bool> & perfect);
void printRoots(const node *root);

#endif
