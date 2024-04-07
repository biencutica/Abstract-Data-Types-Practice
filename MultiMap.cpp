#include "MultiMap.h"
#include "MultiMapIterator.h"
#include <exception>
#include <iostream>

using namespace std;

//Constructor
MultiMap::MultiMap() : head{ nullptr }, tail{ nullptr }, count{ 0 }, keycount{ 0 } {}


void MultiMap::add(const TKey& key, const TValue& value)
{
	//Best Case: theta(1), when multimap is empty and a new node is created
	//Worst Case: theta(n), when the multimap is not empty and the key being added is already in the list
	//Average Case: O(n), depends on the average number of nodes needed to be traversed
	//if the head is null, means there are no nodes and we need to create one
	if (head == nullptr)
	{
		head = tail = new Node(key, value, nullptr, nullptr);
		keycount++;
		count++;
		return;
	}
	//if the head is not null, iterate through the nodes to find the matching key
	else
	{
		Node* current = head;
		while (current != nullptr && current->key != key)
			current = current->next;

		//if the matching key is not found, create a new node and append it to the end of the list
		if (current == nullptr)
		{
			Node* new_node = new Node(key, value, nullptr, tail);
			tail->next = new_node;
			tail = new_node;
			keycount++;
			count++;
		}

		//if the key exists, add the value to the vector
		else {
			current->values.push_back(value);
			count++;
		}
	}
}


bool MultiMap::remove(const TKey& key, const TValue& value)
{
	//Best Case: theta(1), when multimap is empty or the key is at the head
	//Worst Case: theta(n+k), when the key is at the tail
	//Average Case: O(n+k), depends on average position of the pair
	Node* current = head;
	while (current != nullptr && current->key != key)
		current = current->next;

	if (current != nullptr)
	{
		//search for the value in the vector of values for the given key
		auto it = std::find(current->values.begin(), current->values.end(), value);

		//if the value is found, remove it from the vector
		if (it != current->values.end())
		{
			current->values.erase(it);
			count--;

			// if the vector is now empty, remove the node from the multimap
			if (current->values.empty())
			{
				if (current == head)
				{
					head = current->next;
					if (head != nullptr)
						head->prev = nullptr;
				}
				else if (current == tail)
				{
					tail = current->prev;
					if (tail != nullptr)
						tail->next = nullptr;
				}
				else
				{
					current->prev->next = current->next;
					current->next->prev = current->prev;
				}

				keycount--;
			}
			return true;
		}
	}
	return false;
}


vector<TValue> MultiMap::search(const TKey& key) const
{
	//Best Case: theta(1), when the multimap is empty, or key is at the head
	//Worst Case: theta(n), when key is at the tail or not in the list, traverses entire list
	//Average Case: O(n): depends on the average position of key
	vector<TValue> values;

	//find the node with the given key
	Node* current = head;
	while (current != nullptr && current->key != key)
		current = current->next;

	//if the key is found, add all values to the vector
	if (current != nullptr) {
		for (const auto& value : current->values) {
			values.push_back(value);
		}
	}

	return values;
}


int MultiMap::size() const {
	//Best Case: theta(1), when multimap is empty
	//Worst Case: theta(1), when multimap is not empty
	//Average Case: theta(1)
	//return the number of key-value pairs in the multimap
	return count;
}


bool MultiMap::isEmpty() const {
	//Best Case: theta(1)
	//Worst Case: theta(1)
	//Average Case: theta(1)
	//check if the multimap is empty
	return count == 0;
}


MultiMapIterator MultiMap::iterator() const {
	//Best Case: theta(1)
	//Worst Case: theta(1)
	//Average Case: theta(1)
	//return an iterator to the beginning of the multimap
	return MultiMapIterator(*this);
}

//Destructor
MultiMap::~MultiMap() {
	//Best Case: theta(1), when its empty
	//Worst Case: theta(n), when all n nodes have to be deleted
	//Average Case: O(n), depends on number of nodes in the multimap
	//iterate through the nodes and delete each one
	Node* current = head;
	while (current != nullptr)
	{
		Node* next = current->next;
		delete current;
		current = next;
	}
}