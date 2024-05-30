#include "Item.h"
void Item::Description() const
{
	std::cout << "misc item (belonging in no perticular cathegory)";
}
Item::Item(std::string name_, int count_ = 1) : name{ name_ }, same_item_count{ count_ } {
}

std::string Item::GetName() {
	return this->name;
}

int Item::GetCount() {
	return this->same_item_count;
}

Item::Item() : name{ "" }, same_item_count{0} {}


Item::~Item() {
}


