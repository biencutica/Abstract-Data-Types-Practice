#pragma once

#include<utility>

template<typename T>
class BagIterator;

typedef int TKey;

template<typename T>
class Bag {
private:

	//capacity
	int cp;

	//size
	int n;

	//array of element
	std::pair<TKey, T>* arr;

	//for resizing the dynamic array
	void resize();

public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(T e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(T e);

	//checks if an element appears in the bag
	bool search(T e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(T e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator<T> iterator() const;

	void print() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
