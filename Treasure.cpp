#include "Treasure.h"
double average(double x, double y) {
	return (x + y) / 2;
}
int Treasure::treasure_count_generator = 0;
Treasure::Treasure() : Item("", 0), value(0), different_treasure_count(treasure_count_generator){}
Treasure::Treasure(const std::string name_, double value_, int count_ = 1) : Item(name_, count_), value{ value_ }, different_treasure_count{treasure_count_generator} {
	if(same_item_count != 0)
		different_treasure_count = ++treasure_count_generator;
}
Treasure& Treasure::operator=(const Treasure& other)
{
	if (this != &other) {
		this->name = other.name;
		this->same_item_count = other.same_item_count;
		this->value = other.value;
	}
	return *this;
}

Treasure Treasure::operator+(const Treasure& other) {
	if (this->name == other.name) {
		return Treasure(this->name, average(this->value, other.value), this->same_item_count + other.same_item_count);
	}
	else {
		throw std::logic_error("can't add Treasures of different type");
	}
}

double Treasure::GetValue() {
	return this->value * this->same_item_count;
}

void Treasure::PrintTreasure() {
	if (this->name == "")
		std::cout << "empty\n";
	else
	std::cout << this->same_item_count << " x " << this->name << " = " << value * same_item_count <<"$\n";
}

Treasure::~Treasure() {
	if (same_item_count != 0){
		--treasure_count_generator;
	}
}