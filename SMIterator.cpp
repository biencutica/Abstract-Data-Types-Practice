#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

SMIterator::SMIterator(const SortedMap& m) : map(m){
    first();
}

void SMIterator::first() {
    //BC: O(1) if the BST is empty it only does vec.clear() or has one node
    //WC: O(log n) traverses entire left spine until it reaches the minimum node
    //AC: O(log n) because we still need to traverse to get to the first
	vec.clear();
	currentKey = map.root;
	while (currentKey != NULL_TKEY) {
		vec.push_back(currentKey);
		currentKey = map.nodes[currentKey].left;
	}
    if(!vec.empty())
    {
        currentKey = vec.back();
        vec.pop_back();
    }
}


void SMIterator::next() {
    //BC: O(1) if valid returns false or if there arent any other nodes left
    //WC: O(log n) it enters the while loop traversing the left spine
    //AC:if it's balanced it's O(log n)/skewed - O(n)
    if (!valid())
        throw std::exception("Invalid.");

    if (map.nodes[currentKey].right != NULL_TKEY) {
        currentKey = map.nodes[currentKey].right;
        while (currentKey != NULL_TKEY) {
            vec.push_back(currentKey);
            currentKey = map.nodes[currentKey].left;
        }
    }

    if (!vec.empty()) {
        currentKey = vec.back();
        vec.pop_back();
    }
    else {
        currentKey = NULL_TKEY;
    }
 
}


bool SMIterator::valid() const{
    //O(1)
	return (currentKey != NULL_TKEY);
}

TElem SMIterator::getCurrent() const{
    //O(1)
	if (!valid()) throw exception("Invalid.");
	return map.nodes[currentKey].info;
}


