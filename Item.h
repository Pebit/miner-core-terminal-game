#ifndef ITEM_H_
#define ITEM_H_
#include <iostream>

class Item {
protected:
	std::string name;
	int same_item_count;
public:
	virtual void Description() const;
	std::string GetName();
	int GetCount();
	Item();
	virtual ~Item();
protected:
	Item(std::string name_, int count_);
};

#endif /* ITEM_H_*/