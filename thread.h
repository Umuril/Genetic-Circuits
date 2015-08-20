#ifndef THREAD_H
#define THREAD_H

#include <chrono>
#include <deque>
#include <iostream>
#include <set>
#include <thread>
#include <vector>
#include <mutex>
#include "structs.h"
#include "utility.h"
#include "mutation.h"
#include "debug.h"

void thread_work(std::vector<node> &best_gate, std::vector<size_t> &best_root, size_t & input_lenght,std::vector< std::vector<bool> > & output);

#endif
