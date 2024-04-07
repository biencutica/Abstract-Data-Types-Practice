#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <iostream>
using namespace std;

SortedMap::SortedMap(Relation r) {
	//O(1)
	this->r = r;
	cap = 100;
	sz = 0;
	root = NULL_TKEY;
	nodes = new DLLANode[cap];
	for (int i = 0; i < cap; i++) {
		nodes[i].info = NULL_TPAIR;
		nodes[i].left = NULL_TKEY;
		nodes[i].right = NULL_TKEY;
	}
}

void SortedMap::resize()
{
	int newCap = cap * 2;
	DLLANode* newArray = new DLLANode[newCap];

	for (int i = 0; i < cap; i++) {
		newArray[i] = nodes[i];
	}

	delete[] nodes;
	nodes = newArray;
	cap = newCap;
}


TKey SortedMap::allocate(TKey key, TValue value)
{
	//BC:O(1) when it doesnt need resizing
	//WC:O(cap) needs resizing
	//AC:O(1) amortized
	if (firstEmpty == cap) {
		resize();
	}
	TKey newIndex = firstEmpty;
	nodes[newIndex].info.first = key;
	nodes[newIndex].info.second = value; 
	nodes[newIndex].left = NULL_TKEY;
	nodes[newIndex].right = NULL_TKEY;
	firstEmpty++;
	return newIndex;
}

void SortedMap::deallocate(TKey k)
{
	//BC:O(1)
	//WC:O(1)
	//AC:O(1)
	nodes[k].info.first = NULL_TKEY;
	nodes[k].left = NULL_TKEY;
	nodes[k].right = NULL_TKEY;
	nodes[k].info.second = NULL_TVALUE;
	if (k < firstEmpty)
		firstEmpty = k;
}

TValue SortedMap::add(TKey k, TValue v) {
	//BC:O(1) when its empty
//WC:O(cap) when we need to allocate a new node
//AC:balanced/almost balanced(O log n) - unbalanced (O n)
	if (root == NULL_TKEY) {
		// when tree is empty
		root = allocate(k, v);
		sz++;
		return NULL_TVALUE;
	}
	else {
		int currKey = root;
		while (currKey != NULL_TKEY) {
			if (k == nodes[currKey].info.first) {
				// step 2: when key already exists
				TValue elem = nodes[currKey].info.second;
				nodes[currKey].info.second = v;
				return elem;
			}

			if (r(k, nodes[currKey].info.first)) {
				if (nodes[currKey].left == NULL_TKEY) {
					// decide if we need to insert in the left subtree
					int newIndex = allocate(k, v);
					nodes[currKey].left = newIndex;
					break;
				}
				else
					currKey = nodes[currKey].left;
			}
			else {
				// or insert in the right subtree
				if (nodes[currKey].right == NULL_TKEY) {
					int newIndex = allocate(k, v);
					nodes[currKey].right = newIndex;
					break;
				}
				else
					currKey = nodes[currKey].right;
			}
		}
	}
	sz++;
	return NULL_TVALUE;
}


TValue SortedMap::search(TKey k) const {
	//BC:O(1) when its at the root
	//WC:O(cap) when the key is not present or the tree is empty
	//AC:balanced/almost balanced(O log n) - unbalanced (O n)
    TKey currentIndex = root;
    while (currentIndex != NULL_TKEY) {
        if (k == nodes[currentIndex].info.first)
            return nodes[currentIndex].info.second;
 
        if (r(k, nodes[currentIndex].info.first))
            currentIndex = nodes[currentIndex].left;
        else
            currentIndex = nodes[currentIndex].right;
    }
    return NULL_TVALUE;
}


TValue SortedMap::remove(TKey k) {
	//BC:O(1) when tree is empty
	//WC: O(n) if its a leaf
	//AC:balanced/almost balanced(O log n) - unbalanced (O n)
	TKey currentIndex = root;
	if (currentIndex == NULL_TKEY) // if the tree is empty
		return NULL_TVALUE;
	TKey parentIndex = NULL_TKEY;
	//search for the key
	while (currentIndex != NULL_TKEY && k != nodes[currentIndex].info.first) {
		parentIndex = currentIndex;

		if (r(k, nodes[currentIndex].info.first)) {
			currentIndex = nodes[currentIndex].left;
		}
		else {
			currentIndex = nodes[currentIndex].right;
		}
	}
	//check if the key was found
	if (currentIndex == NULL_TKEY) {
		return NULL_TVALUE;
	}
	TValue v = nodes[currentIndex].info.second; //store the value of the node to be removed
	if (nodes[currentIndex].right == NULL_TKEY && nodes[currentIndex].left == NULL_TKEY) {
		//case 1: node is a leaf
		if (parentIndex == NULL_TKEY) {
			//we are in the root
			root = NULL_TKEY;
		}
		else {
			if (currentIndex == nodes[parentIndex].left)
				nodes[parentIndex].left = NULL_TKEY;
			else
				nodes[parentIndex].right = NULL_TKEY;
		}
		deallocate(currentIndex);
	}
	else if (nodes[currentIndex].left == NULL_TKEY) {
		//case 2: node has only right child
		TKey rightIndex = nodes[currentIndex].right;
		if (parentIndex == NULL_TKEY)
			root = rightIndex;
		else {
			if (currentIndex == nodes[parentIndex].left)
				nodes[parentIndex].left = rightIndex;
			else
				nodes[parentIndex].right = rightIndex;
		}
		deallocate(currentIndex);
	}
	else if (nodes[currentIndex].right == NULL_TKEY) {
		//case 3: has only left child
		TKey leftIndex = nodes[currentIndex].left;
		if (parentIndex == NULL_TKEY)
			root = leftIndex;
		else {
			if (currentIndex == nodes[parentIndex].left)
				nodes[parentIndex].left = leftIndex;
			else
				nodes[parentIndex].right = leftIndex;
		}
		deallocate(currentIndex);
	}
	else {
		//case 3: node has two children
		//find the node with the maximum key
		TKey replaceIndex = nodes[currentIndex].left;
		while (nodes[replaceIndex].right != NULL_TKEY) {
			replaceIndex = nodes[replaceIndex].right;
		}
		//replace the key and value of current node with the key and value of the found node
		nodes[currentIndex].info = nodes[replaceIndex].info;
		deallocate(replaceIndex);
	}
	//update the size
	sz--;
	return v;
}


int SortedMap::size() const {
	return sz;
}

bool SortedMap::isEmpty() const {
	return sz == 0;
}

SMIterator SortedMap::iterator() const {
	return SMIterator(*this);
}

SortedMap::~SortedMap() {
	delete[] nodes;
}
