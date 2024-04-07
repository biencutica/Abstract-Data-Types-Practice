#pragma once
//DO NOT INCLUDE BAGITERATOR

#include<utility>

//DO NOT CHANGE THIS PART

#define MAX 1000000 //maximum number of locations in the table

typedef int TElem;
typedef std::pair<TElem, int> TPair;
#define NULL_TELEM -1111111
#define NULL_TPAIR std::pair<int, int>(NULL_TELEM, 0)

class BagIterator; 

class Bag {

private:
	int nr; //number of elements
	int m; //number of locations in the hash table
	TPair e[MAX]; //the array of elements - vector static
	int next[MAX]; //the array of links
	int firstEmpty; // the first empty position in the hash table

	void updateFirstEmpty();
	int h(TElem e); //the hash function

	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appears in the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
