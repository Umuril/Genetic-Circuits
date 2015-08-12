#include <tuple>	// std::tie
#include <memory>	// std::shared_ptr

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
