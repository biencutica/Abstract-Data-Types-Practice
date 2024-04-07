#pragma once
#include "SortedMap.h"
#include<vector>
//DO NOT CHANGE THIS PART
class SMIterator{
	friend class SortedMap;
private:
	const SortedMap& map;
	TKey currentKey;
	SMIterator(const SortedMap& mapionar);
	std::vector<TKey> vec;
public:
	void first();
	void next();
	bool valid() const;
    TElem getCurrent() const;
};

