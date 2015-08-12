#ifndef UTILITY_H
#define UTILITY_H

#include <chrono>
#include <algorithm>
#include <deque>
#include <fstream>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "structs.h"

void addWeight(	node * node_pointer,
				const bool & perfect,
				const std::set<weighted_pointer> & gate);
bool exec(node root);
int fitness(const std::vector<node *> &root,
			std::deque<bool> & input,
			const std::vector< std::vector<bool> > &output,
			const std::set<weighted_pointer> & gate,
			std::vector<bool> & perfect);

#endif
