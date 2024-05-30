#ifndef PLAYER_H_
#define PLAYER_H_
#include "Tool.h"
#include <iostream>
#include <ctime>
#include "Treasure.h"
#include "PlayerInterface.h"

class Player : public PlayerInterface {
private:
	Tool tool;
	int hotb_size;
	Treasure* hotbar;
	double money;
public:
	static int ValueInRange1To(int x);
	
	Player(const Player& other);
	// operator= atribuire prin copiere
	Player& operator=(const Player& other);
	// constructor de mutare
	Player(Player&& other) noexcept;
	// operator= atribuire prin mutare
	Player& operator=(Player&& other) noexcept;

	friend std::ostream& operator<<(std::ostream& os, const Player& player);

	void AddTreasure(Treasure treasureitem) override;
	void UpgradeHotbar() override;
	void SellHotbar() override;
	void PrintHotbar() override;
	void UpgradeTool(float efficiency, int durability) override;
	void SellItem(std::string item_name);
	int ToolEfficiency() override;
	Player();
	~Player();
};
#endif /* PLAYER_H_*/