#ifndef TOOL_H_
#define TOOL_H_
#include "Item.h"
#include <iostream>
class Tool : public Item {
protected:
	int efficiency;
	int durability;
public:
	Tool(std::string name_, int efficiency_, int durability_, int count_);
	Tool();
	void Upgrade(float efficiency_, int durability_);
	int GetEfficiency();
	void Wear();
	Tool& operator=(const Tool& other);
	~Tool() override;
};
#endif /* TOOL_H_*/