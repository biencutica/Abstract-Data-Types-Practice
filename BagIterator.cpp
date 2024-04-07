#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

template<typename T>
BagIterator<T>::BagIterator(const Bag<T>& c) : bag(c) //Initalizer
{
	// bc:theta(1)
	// wc:theta(1)
	// overall:theta(1)
	occurence = 1;
	current = 0;
}

template<typename T>
void BagIterator<T>::first() { //Set current to be at the first element
	// bc:theta(1)
	// wc:theta(1)
	// overall:theta(1)
	occurence = 1;
	current = 0;
}

template<typename T>
void BagIterator<T>::next() {
	//bc:theta(n)
	//wc:theta(n)
	//overall:theta(n)

	//We move to the next element, if possible, else throws an exception
	if (!valid()) {
		throw exception();
	}
	else {
		if (occurence == bag.arr[current].first) {
			current++;
			occurence = 1;
		}
		else
			occurence++;
	}
}

template<typename T>
bool BagIterator<T>::valid() const {
	//bc:theta(n)
	//wc:theta(n)
	//overall:theta(n)

	//returns true if the current is still in the bag, false otherwise
	return  (current < bag.n);
}


template<typename T>
T BagIterator<T>::getCurrent() const
{
	//bc:theta(n)
	//wc:theta(n)
	//overall:theta(n)

	if (!valid()) {
		throw exception();
	}
	else {
		return this->bag.arr[current].second;
	}
}
