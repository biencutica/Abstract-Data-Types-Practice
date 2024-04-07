#include "BagIterator.h"
#include"Bag.h"
#include <exception>
#include <iostream>
using namespace std;

template<typename T>
void Bag<T>::resize() {
	// theta(n)
	// bc:theta(n)
	// wc:theta(n)
	// overall:theta(n)

	//We allocate a new array with double capacity somewhere in the computer's memory
	std::pair<TKey, T>* eNou = new std::pair<TKey, T>[2 * cp];

	//We copy all the elements from the old array into the new array
	for (int i = 0; i < n; i++) { //theta(n)
		eNou[i] = arr[i];
	}

	//We double the capacity
	cp = 2 * cp;

	//We release the memory space occupied by the old array
	delete[] arr;

	//We make eNou to refer the new array (with double capacity)
	arr = eNou;
}

template<typename T>
Bag<T>::Bag() { //Uniform Initializer 
	// theta(1)
	// bc:theta(1)
	// wc:theta(1)
	// overall:theta(1)

	//We initialize the capacity
	cp = 1;

	//We allocate memory space for an array with at most cp TPairs
	arr = new std::pair<TKey, T>[cp];

	//We initialize the number of elements
	n = 0;

}

template<typename T>
void Bag<T>::add(T elem) {
	// theta(n)
	// bc:theta(n)
	// wc:theta(n)
	// overall:theta(n)

	//If the maximum capacity has been reached, then we resize the array of elements
	if (n == cp)
		resize(); //theta(n)

	//We iterate through the array and check if we find the element
	//If so, we +1 the number of occurences
	int ok = 0;
	for (int i = 0; i < n; i++) //theta(n)
	{
		if (arr[i].second == elem) {
			arr[i].first++;
			ok = 1;
		}
	}

	//If the number is not in the list
	//We add the element to the end of the array
	if (ok != 1) {
		arr[n].second = elem;
		arr[n++].first = 1;
	}
}

template<typename T>
bool Bag<T>::remove(T elem) {
	// bc:theta(n)
	// wc:theta(n)
	// overall:theta(n)

	//We start searching for the element to be deleted (one occurrence only!) from index 0
	bool found = false;
	int i = 0;
	//While we still have elements to compare the element and the element hasn't been found
	while (i < n && !found) { //theta(n)
		//We compare the current element with the one to be deleted
		//If they are equal
		if (arr[i].second == elem) {
			//We just found the element
			found = true;
			//We also remove it's occurence 
			arr[i].first--;
			//If the number of it's occurences is 0, we delete it by shifting all the elements starting from index i+1 one position to the left
			if (arr[i].first == 0) {
				for (int j = i; j < n - 1; j++) {
					arr[j] = arr[j + 1];
				}
				n--; //And we decrement the size
			}
		}
		else {
			//, then we just increase the index in order to advance in traversing the array of elements
			i++;
		}
	}
	//We return if we managed to remove an element (found = true if removed, false otherwise)
	return found;
}

template <typename T>
bool Bag<T>::search(T elem) const {
	// bc:theta(1)
	// wc:theta(n)
	// overall:O(n)

	//We traverse the array of elements
	for (int i = 0; i < n; i++) {
		//and compare each element in the array with the element we are searching for
		//If the two are equal then we just return true (and exit the loop)
		if (arr[i].second == elem)
			return true;
	}
	//If the element hasn't been found, we return false
	return false;
}

template<typename T>
int Bag<T>::nrOccurrences(T elem) const {
	// bc:theta(1)
	// wc:theta(n)
	// overall:O(n)

	//We traverse the array of elements
	for (int i = 0; i < n; i++)
		//If the element has been found
		if (arr[i].second == elem)
			//we return the number of it's occurences
			return arr[i].first;
	//if the number hasn't been found, we just return 0
	return 0;
}

template<typename T>
int Bag<T>::size() const {
	//bc:theta(n)
	//wc:theta(n)
	//overall:theta(n)

	//we initialize nr as the size of the bag, representing the number of all the elements in the array with 0
	int nr = 0;
	//we go through the array and count all the number of occurences of each element
	for (int i = 0; i < n; i++)
		nr += arr[i].first;
	//and we return the number of elements, i.e. the size
	return nr;
}

template<typename T>
bool Bag<T>::isEmpty() const {
	// bc:theta(1)
	// wc:theta(1)
	// overall:theta(1)
	//The bag is empty if and only if the current number of elements is 0
	return (n == 0);
}

template<typename T>
BagIterator<T> Bag<T>::iterator() const {
	// bc:theta(1)
	// wc:theta(1)
	// overall:theta(1)

	return BagIterator<T>(*this);
}

template<typename T>
void Bag<T>::print() const {
	// Iterate through the array of elements
	for (int i = 0; i < n; i++) {
		// Print the element and its number of occurrences
		cout << arr[i].second << ": " << arr[i].first << endl;
	}
}

template<typename T>
Bag<T>::~Bag() {
	// bc:theta(1)
	// wc:theta(1)
	// overall:theta(1)

	//We free the memory space allocated for the array of elements
	delete[] arr;
}