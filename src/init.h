#ifndef INIT_H
#define INIT_H

#include <deque>		// std::deque
#include <fstream>		// std::ifstream
#include <vector>		// std::vector, std::vector<bool>

bool read_output_from_file(	const char *FILENAME,std::vector< std::vector<bool> > &output, size_t &input_lenght);

#endif
