#pragma once
#include<vector>
#include<utility>
//DO NOT INCLUDE MultiMapIterator

using namespace std;

//DO NOT CHANGE THIS PART
typedef int TKey;
typedef int TValue;
typedef pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<int,int>(-111111, -111111)

struct Node {
	TKey key;
	vector<TValue> values;
	Node* next;
	Node* prev;

	Node(const TKey& tkey, const TValue& tvalue, Node* tnext = nullptr, Node* tprev = nullptr) { key = tkey; next = tnext; prev = tprev; values.push_back(tvalue); }
};

class MultiMapIterator;

class MultiMap
{
	friend class MultiMapIterator;

protected:
	Node* head;
	Node* tail;
	int count; //number of elements
	int keycount; //number of keyst

public:
	//constructor
	MultiMap();

	//adds a key value pair to the multimap
	void add(const TKey& key, const TValue& value);

	//removes a key value pair from the multimap
	//returns true if the pair was removed (if it was in the multimap) and false otherwise
	bool remove(const TKey& key, const TValue& value);

	//returns the vector of values associated to a key. If the key is not in the MultiMap, the vector is empty
	vector<TValue> search(const TKey& key) const;

	//returns the number of pairs from the multimap
	int size() const;

	//checks whether the multimap is empty
	bool isEmpty() const;

	//returns an iterator for the multimap
	MultiMapIterator iterator() const;

	//destructor
	~MultiMap();

};