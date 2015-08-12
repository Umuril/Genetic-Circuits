#ifndef INIT_H
#define INIT_H

#include <chrono>
#include <deque>
#include <fstream>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "structs.h"

bool read_output_from_file(std::vector< std::vector<bool> > &output,size_t &input_lenght);
void init(std::deque<bool> &input, const std::vector< std::vector<bool> > &output, std::set<weighted_pointer> &gate, std::vector<node *> &root);

#endif
