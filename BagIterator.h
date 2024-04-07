#include "Bag.h"

template<typename T>
class BagIterator
{
private:
	const Bag<T>& bag;
	int current;
	int occurence;
	BagIterator(const Bag<T>& c);
public:
	void first();
	void next();
	T getCurrent() const;
	bool valid() const;
};
