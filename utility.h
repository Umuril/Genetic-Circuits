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
#include <iostream>
#include "structs.h"

bool exec(node root,std::deque<bool> & input,std::vector<node> & gate);
int fitness(std::vector<node> &gate, std::vector<size_t> &root, const size_t &input_lenght,const std::vector< std::vector<bool> > &output);

#endif
