#ifndef TREASURE_H_
#define TREASURE_H_
#include "Item.h"
class Treasure : public Item {
private:
	static int treasure_count_generator;
protected:	
	double value;
	int different_treasure_count;
public:
	Treasure(const std::string name_, double value_, int count_);
	Treasure();
	
	Treasure operator+(const Treasure& other);
	Treasure& operator=(const Treasure& other);

	double GetValue();
	void PrintTreasure();

	~Treasure() override;
};
#endif /* TREASURE_H_*/