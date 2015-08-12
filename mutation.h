#ifndef MUTATION_H
#define MUTATION_H

#include <algorithm>
#include <chrono>
#include <deque>
#include <fstream>
#include <iterator>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "structs.h"

void changeRoots(std::vector<node *> &root, std::set<weighted_pointer> & gate);
void tryAdd(std::set<weighted_pointer> & gate);
void tryRemove(std::set<weighted_pointer> & gate, std::deque<bool> & input,std::vector<node *> root);
void randomize(std::set<weighted_pointer> & gate,std::deque<bool> & input,std::vector<node*> & root);

#endif
