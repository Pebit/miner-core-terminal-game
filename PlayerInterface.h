#ifndef PLAYERINTERFACE_H_
#define PLAYERINTERFACE_H_
#include "Treasure.h"
class PlayerInterface {
protected:
	virtual void AddTreasure(Treasure treasureitem) = 0;
	virtual void PrintHotbar() = 0;
	virtual void UpgradeHotbar() = 0;
	virtual void SellHotbar() = 0;
	virtual void UpgradeTool(float efficiency, int durability) = 0;
	virtual int ToolEfficiency() = 0;
	/*
	virtual void Mine() = 0;
	virtual void const Save() = 0;*/
};
#endif /* PLAYERINTERFACE_H_*/