#ifndef DEBUG_H
#define DEBUG_H

#include <deque>		// std::deque
#include <iostream>		// std::cout
#include <fstream>		
#include <vector>		// std::vector, std::vector<bool>
#include "structs.h"	// struct node
#include "utility.h"

void print(std::ostream & os, std::vector<node> &gate, std::vector<size_t> &root,const size_t &input_lenght,const std::vector< std::vector<bool> > &output);
void printData(std::ostream & os, std::vector<node> &gate, std::vector<size_t> &root,const size_t & input_lenght,const std::vector< std::vector<bool> > &output);
void printGate(std::ostream & os, const std::vector<node> &gate);
void printRoot(std::ostream & os, const std::vector<size_t> &root);

#endif
