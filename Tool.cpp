#include "Tool.h"
#include <limits.h>
Tool::Tool() : Item("fists", 1), efficiency(1), durability(INT_MAX){}
Tool::Tool(std::string name_, int efficiency_, int durability_, int count_ = 1) : Item(name_, count_), efficiency{ efficiency_ }, durability{ durability_ } {}

Tool& Tool::operator=(const Tool& other)
{
	if (this != &other) {
		this->name = other.name;
		this->same_item_count = other.same_item_count;
		this->efficiency = other.efficiency;
		this->durability = other.durability;
	}
	return *this;
}

void Tool::Upgrade(float efficiency_, int durability_) {
	this->efficiency = this->efficiency + efficiency;
	this->durability = this->durability + durability_;
}
int Tool::GetEfficiency() {
	return this->efficiency;
}
void Tool::Wear() {
	this->durability--;
	if (this->durability == 0);
	{
		this->name = "fists";
		this->efficiency = 1;
		this->durability = 99999999;
	}
}

Tool::~Tool(){
}
