#ifndef DEBUG_H
#define DEBUG_H

#include <chrono>
#include <deque>
#include <fstream>
#include <iostream>
#include <memory>
#include <set>
#include <utility>
#include <vector>
#include "structs.h"
#include "utility.h"

void print(const std::deque<bool> & input,const std::vector< std::vector<bool> > & output,const std::vector<node *> & root);
void printData(const std::deque<bool> & input,const std::vector< std::vector<bool> > & output,const std::vector<node *> & root);
void printRoots(const node *root);

#endif