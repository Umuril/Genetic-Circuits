#ifndef STRUCTS_H
#define STRUCTS_H

#include <memory>	// std::shared_ptr
#include <set>		// std::set
#include <tuple>	// std::tie
#include <vector>	// std::vector

struct node {
	unsigned int oper : 3;
	void *a;
	void *b;
	
	bool operator < (const node & rhs) const {
		return std::tie(oper,a,b) < std::tie(rhs.oper,rhs.a,rhs.b);	
	}
};

struct weighted_pointer {
	mutable int weight;
	std::shared_ptr<node> pointer;
	
	bool operator < (const weighted_pointer & rhs) const {
		return pointer < rhs.pointer;
	}
};

struct backup {
	std::set<weighted_pointer> gate;
	std::vector<node *> root;
	
	void create_backup(const std::set<weighted_pointer> & p_gate, const std::vector<node *> p_root){
		gate.clear();
		gate.insert(p_gate.begin(),p_gate.end());
		root.asign(p_root.begin(),p_root.end());
	}
	
	void restore_from_backup(std::set<weighted_pointer> & p_gate, std::vector<node *> p_root){
		p_gate.clear();
		p_gate.insert(gate.begin(),gate.end());
		p_root.asign(root.begin(),root.end());
	}
	
};

#endif
