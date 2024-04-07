#include "MultiMapIterator.h"
#include "MultiMap.h"


MultiMapIterator::MultiMapIterator(const MultiMap& c): col(c) {
    //Best Case: theta(1), when the head is nullptr
    //Worst Case: theta(n), when the head is the last node
    //Average Case: O(n), depends on the position of head
	current = col.head;
    valueIndex = 0;
}

TElem MultiMapIterator::getCurrent() const{
    //Best Case: theta(1)
    //Worst Case: theta(1)
    //Average Case: theta(1)
    if (!valid())
        throw exception();
  
    const Node* currentNode = current;

    // if the current node is not null, return its key-value pair
    if (currentNode != nullptr) {
        return { currentNode->key, currentNode->values[currentNode->values.size() - 1] };
    }

    // otherwise return a null TElem
    return NULL_TELEM;
}

bool MultiMapIterator::valid() const {
    //Best Case: theta(1)
    //Worst Case: theta(1)
    //Average Case: theta(1)
    return current != nullptr;
}

void MultiMapIterator::next() {
    //Best Case: theta(1)
    //Worst Case: theta(1)
    //Average Case: theta(1)
    if (!valid())
        throw exception();

    const Node* currentNode = current;

    // if there are more values in the current node, move to the next value
    if (valueIndex < currentNode->values.size() - 1) {
        valueIndex++;
        return;
    }

    // otherwise, move to the next node
    valueIndex = 0;
    current = current->next;
}

void MultiMapIterator::first() {
    //Best Case: theta(1)
    //Worst Case: theta(1)
    //Average Case: theta(1)
    current = col.head;
}

