#include "Bag.h"

class BagIterator
{
	//DO NOT CHANGE THIS PART
	friend class Bag;
	
private:
	const Bag& bag;
	//the current location in the hash table
	int current;
	//moving the cursor to the next non-empty position
	void move();
	BagIterator(const Bag& c);
	int index;
public:
	void first();
	void next();
	TElem getCurrent() const;
	bool valid() const;
};
