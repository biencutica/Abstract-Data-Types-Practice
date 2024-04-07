#include "Bag.h"
#include "BagIterator.h"
#include <iostream>
#include <exception>
#include <math.h>
using namespace std;

//function that gives the hashCode of an element
int hashCode(TElem e){
   return abs(e);
}

//the hash function
int Bag::h(TElem e) {
	//division method
	return hashCode(e) % m;
}


Bag::Bag() {
	//Best Case: theta(m) 
	//Worst Case: theta(m)  
	//Average Case: theta(m)

	nr = 0;
    m = MAX; //we initialize m with a high enough predefined value
	for (int i = 0; i < m; i++) {
		e[i] = NULL_TPAIR;
		next[i] = -1;
	}
	firstEmpty = 0;
}


void Bag::updateFirstEmpty(){
	//Best Case: theta(1) 
	//Worst Case: theta(m)  
	//Average Case: O(m)

	firstEmpty++;
	while (firstEmpty < m && e[firstEmpty].first != NULL_TELEM)
		firstEmpty++;
}


// adding an element into the bag
void Bag::add(TElem elem) {
	//Best Case: theta(1) : if the position is free 
	//Worst Case: theta(m) : it iterates through the whole chain
	//Average Case: O(m) : we find the element while iterating
	
	// the hash
	int i = h(elem);
	if (e[i].first == NULL_TELEM)	// if the position is free
	{
		e[i] = TPair(elem, 1);	// we add the element
		if (i == firstEmpty)
			updateFirstEmpty();	// we update first empty, if needed
		nr++;
		return;
	}

	// if the position is not free
	int prev = -1;	// j will be the previous of i
	while (i != -1)	// we are iterating to the end of the chaining
	{
		if (e[i].first == elem) { //if somehow by iterating we find the element
			e[i].second++;
			nr++;
			return;
		}
		prev = i;
		i = next[i];
	}

	// if we didnt find the element
	// we are assuming that m is high-enough
	e[firstEmpty] = TPair(elem, 1);
	next[prev] = firstEmpty;
	updateFirstEmpty();
	nr++;
}

bool Bag::remove(TElem elem){
	//Best Case: theta(1) : when the elem is in the list and we decrement the frequency
	//Worst Case: theta(m) : it's the first one in the chain
	//Average Case: O(m) : when the element is the last one in the chain

	int i = h(elem);
	int prev = -1; // to store the previous hash in the chain

	// iterate through the whole list
	while (i != -1) {
		if (e[i].first == elem) {
			if (e[i].second > 1) {
				e[i].second--;
			}
			else {
				e[i] = NULL_TPAIR;
				while (next[i] != -1) { //shift all elements in the chain
					e[i] = e[next[i]];
					prev = i;
					i = next[i];
				}
				e[i] = NULL_TPAIR; //empty the last slot of the chain 
				if(prev != -1)
					next[prev] = -1; // and set it's next to -1

			}
			nr--;
			return true;
		}
		prev = i;
		i = next[i];
	}
	return false;
}



bool Bag::search(TElem elem) const{
	//Best Case: theta(1) : if it's the first in the list
	//Worst Case: theta(m) : if it doesn't exist
	//Average Case: O(m) : if it's in the middle

	for (auto el : e)
		if (el.first == elem)
			return true;
	return false;
}

int Bag::nrOccurrences(TElem elem) const{
	//Best Case: theta(1) : if it's the first in the list
	//Worst Case: theta(m) : if it doesn't exist
	//Average Case: O(m) : if it's in the middle

	for (auto el : e)
		if (el.first == elem)
			return el.second;
	return 0;
}

int Bag::size() const
{
	return nr;
}

BagIterator Bag::iterator() const{
	return BagIterator(*this);
}

bool Bag::isEmpty() const
{
	return nr == 0;
}

Bag::~Bag() {
}




