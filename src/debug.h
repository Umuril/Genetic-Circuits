#ifndef DEBUG_H
#define DEBUG_H

#include <deque>
#include <iostream>
#include <fstream>
#include <vector>
#include "structs.h"
#include "utility.h"

void print(std::ostream & os, const std::vector<node> & gate,
			const std::vector<size_t> & root, const size_t & input_lenght, 
			const std::vector< std::vector<bool> > & output);
void printData(std::ostream & os, const std::vector<node> & gate,
				const std::vector<size_t> & root, const size_t & input_lenght,
				const std::vector< std::vector<bool> > & output);
void printGate(std::ostream & os, const std::vector<node> & gate);
void printRoot(std::ostream & os, const std::vector<size_t> & root);

#endif
