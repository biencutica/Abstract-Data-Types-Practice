#include <exception>
#include "BagIterator.h"
#include "Bag.h"

void BagIterator::move() {
	//Best Case: theta(1) 
	//Worst Case: theta(m) 
	//Average Case: O(m)
	while ((current < bag.m) && bag.e[current] == NULL_TPAIR)
		current++;
}

//constructor BagIterator
BagIterator::BagIterator(const Bag& col) :
		bag(col) {
	current = 0;
	index = 1;
	move();
}

void BagIterator::first() {
	//Best Case: theta(1) 
	//Worst Case: theta(1)  
	//Average Case: theta(1)

	current = 0;
	index = 1;
	move();
}

void BagIterator::next() {
	//Best Case: theta(1) 
	//Worst Case: theta(m)  
	//Average Case: O(m)

	if (!valid()){
			throw std::exception();
	}
	if (index == bag.e[current].second) {
		current++;
		index = 1;
		move();
	}
	else {
		index++;
	}

}

bool BagIterator::valid() const {
	//Best Case: theta(1) 
	//Worst Case: theta(1)  
	//Average Case: theta(1)

	return (current < bag.m);
}

TElem BagIterator::getCurrent() const {
	//Best Case: theta(1) 
	//Worst Case: theta(1)  
	//Average Case: theta(1)

	if (!valid()){
			throw std::exception();
	}
	return bag.e[current].first;
}
