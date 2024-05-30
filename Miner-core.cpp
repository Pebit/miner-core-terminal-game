#include <iostream>
#include <string>
#include <ctime>
#include "ObjectsLibrary.h"
#include <chrono>
#include <thread>
#include <windows.h>

// Treasure(const std::string name_, double value_, int count_)
Treasure grass("grass", 0.1, 1);
Treasure stick("stick", 0.2, 1);
Treasure dirt("dirt", 0.05, 1);
Treasure flint("flint", 0.5, 1);
Treasure stone("stone", 2, 1);
Treasure coolrock("cool rock", 5, 1);
Treasure coal("coal", 10, 1);
Treasure iron("iron", 50, 1);
Treasure silver("silver", 120, 1);
Treasure gold("gold", 420, 1);
Treasure emerald("emerald", 700, 1);
Treasure diamond("diamond", 1500, 1);
Treasure rare_fossil("rare fossil", 5000, 1);

// Tool(std::string name_, int efficiency_, int durability_, int count_)
Tool stone_pickaxe("stone pickaxe", 2, 100, 1);
Tool iron_pickaxe("iron pickaxe", 3, 100, 1);
Tool drill("drill", 4, 100, 1);
Tool terraformer("THE TERRAFORMER", 9999, 99999999, 1);

void FlushInputBuffer() {
	// Flush the console input buffer to discard any pending input events
	HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
	if (hInput == INVALID_HANDLE_VALUE) {
		std::cerr << "Error getting standard input handle" << std::endl;
		return;
	}

	if (!FlushConsoleInputBuffer(hInput)) {
		std::cerr << "Error flushing console input buffer" << std::endl;
	}
}

void ForestLoot(Player& player) {
	if (Player::ValueInRange1To(2) != 1)
		player.AddTreasure(dirt);
	else
		if (Player::ValueInRange1To(3) == 1)
			player.AddTreasure(grass);
		else
			if (Player::ValueInRange1To(3) != 1)
				player.AddTreasure(stick);
			else
				player.AddTreasure(flint);
}

void ShallowMineLoot(Player& player) {
	int randomValue = Player::ValueInRange1To(100);
	if (randomValue < 50) {
		player.AddTreasure(stone); // 50% chance
	}
	else if (randomValue < 70) {
		player.AddTreasure(dirt); // 20% chance
	}
	else if (randomValue < 85) {
		player.AddTreasure(flint); // 15 % chance
	}
	else if (randomValue < 95) {
		player.AddTreasure(coal); // 10 % chance
	}
	else {
		player.AddTreasure(iron); // 5 % chance
	}
}

void DeepMineLoot(Player& player) {
	int randomValue = Player::ValueInRange1To(100);
	if (randomValue < 50) {
		player.AddTreasure(stone); // 50% chance
	}
	else if (randomValue < 58) {
		player.AddTreasure(dirt); // 8% chance
	}
	else if (randomValue < 66) {
		player.AddTreasure(flint); // 8 % chance
	}
	else if (randomValue < 83) {
		player.AddTreasure(coal); // 17 % chance
	}
	else if (randomValue < 93) {
		player.AddTreasure(iron); // 10 % chance
	}
	else if (randomValue < 97) {
		player.AddTreasure(silver); // 4 % chance
	}
	else {
		player.AddTreasure(gold); // 3 % chance
	}
}

void ProsperousMineLoot(Player& player) {
	// stone 448/1000, 
	int randomValue = Player::ValueInRange1To(1000);
	if (randomValue < 200) {
		player.AddTreasure(coal); // 20% chance
	}
	else if (randomValue < 300) {
		player.AddTreasure(silver); // 10% chance
	}
	else if (randomValue < 450) {
		player.AddTreasure(iron); // 15% chance
	}
	else if (randomValue < 500) {
		player.AddTreasure(gold); // 5% chance
	}
	else if (randomValue < 530) {
		player.AddTreasure(emerald); // 3% chance
	}
	else if (randomValue < 540) {
		player.AddTreasure(diamond); // 1% chance
	}
	else if (randomValue < 550) {
		player.AddTreasure(flint); // 1% chance
	}
	else if (randomValue < 552) {
		player.AddTreasure(rare_fossil); // 0.2% chance
	}
	else {
		player.AddTreasure(stone); // 44.8% chance
	}
}

void SleepForSeconds(const double x) {
	std::this_thread::sleep_for(std::chrono::milliseconds((int)(x * 1000)));
	FlushInputBuffer();
}

void Mine(Player& player) {
	
	srand(time(0));
	printf("Choose Map to Forage:\n 1 FOREST\n");
	if (player.ToolEfficiency() >= Shallow_Mine)
		printf(" 2 SHALLOW Mine\n");
	if (player.ToolEfficiency() >= Deep_Mine)
		printf(" 3 DEEP Mine\n");
	if (player.ToolEfficiency() >= Prosperous_Mine)
		printf(" 4 PROSPEROUS Mine\n");
	int place = 0;
	while(place <  1 or place > player.ToolEfficiency())
	{
		std::cin >> place;
		if (place < 1 or place > player.ToolEfficiency())
			printf("type a number between \"1\" and \"%d\"\n", player.ToolEfficiency());
	}
	switch (place) {
	case Forest: {
		int breakpower;
		if (player.ToolEfficiency() < 3)
			breakpower = 7 - 2 * player.ToolEfficiency();
		else
			breakpower = 1;
		int increment = 0;
		
		std::cout << " ENTER - mine\n I - inventory\n other - stop mining\n";
		std::string line;
		std::getline(std::cin, line);
		std::getline(std::cin, line);
		while (line == "I" || line == "i" || line == "inv" || line == "inventory"){
			player.PrintHotbar();
			std::getline(std::cin, line);
		}
		
		while (line.empty())
		{
				std::cout << "mining...";
				increment++;
				if (increment >= breakpower)
				{
					ForestLoot(player);
					increment = 0;
				}
				SleepForSeconds((double)1 / player.ToolEfficiency());
			std::getline(std::cin, line);
			while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
				player.PrintHotbar();
				std::getline(std::cin, line);
			}
		}
		break;
	}
	case Shallow_Mine:{
		int breakpower;
		if (player.ToolEfficiency() < 4)
			breakpower = 8 - 2 * player.ToolEfficiency();
		else
			breakpower = 1;
		int increment = 0;

		std::cout << " ENTER - mine\n I - hotbar\n other - stop mining\n";
		std::string line;
		std::getline(std::cin, line);
		std::getline(std::cin, line);
		while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
			player.PrintHotbar();
			std::getline(std::cin, line);
		}

		while (line.empty())
		{
			std::cout << "mining...";
			increment++;
			if (increment >= breakpower)
			{
				ShallowMineLoot(player);
				increment = 0;
			}
			SleepForSeconds((double)1 / player.ToolEfficiency());
			std::getline(std::cin, line);
			while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
				player.PrintHotbar();
				std::getline(std::cin, line);
			}
		}
		break;
	}
	case Deep_Mine:{
		int breakpower;
		if (player.ToolEfficiency() < 5)
			breakpower = 10 - 2 * player.ToolEfficiency();
		else
			breakpower = 1;
		int increment = 0;

		std::cout << " ENTER - mine\n I - hotbar\n other - stop mining\n";
		std::string line;
		std::getline(std::cin, line);
		std::getline(std::cin, line);
		while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
			player.PrintHotbar();
			std::getline(std::cin, line);
		}

		while (line.empty())
		{
			std::cout << "mining...";
			increment++;
			if (increment >= breakpower)
			{
				DeepMineLoot(player);
				increment = 0;
			}
			SleepForSeconds((double)1 / player.ToolEfficiency());
			std::getline(std::cin, line);
			while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
				player.PrintHotbar();
				std::getline(std::cin, line);
			}
		}
		break;
	}
	case Prosperous_Mine: {
		int breakpower;
		if (player.ToolEfficiency() < 5)
			breakpower = 11 - 2 * player.ToolEfficiency();
		else
			breakpower = 2;
		int increment = 0;

		std::cout << " ENTER - mine\n I - hotbar\n other - stop mining\n";
		std::string line;
		std::getline(std::cin, line);
		std::getline(std::cin, line);
		while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
			player.PrintHotbar();
			std::getline(std::cin, line);
		}

		while (line.empty())
		{
			std::cout << "mining...";
			increment++;
			if (increment >= breakpower)
			{
				ProsperousMineLoot(player);
				increment = 0;
			}
			SleepForSeconds((double)1 / player.ToolEfficiency());
			std::getline(std::cin, line);
			while (line == "I" || line == "i" || line == "inv" || line == "hotbar") {
				player.PrintHotbar();
				std::getline(std::cin, line);
			}
		}
		break;
	}
	default:
		std::cout << "this place does not exist";
		break;
	}
}

void Craft(Player& player) {

}

int main()
{
	Player player;
	player.PrintHotbar();
	std::cout << std::endl;
	bool gameloop = 1;
	while (gameloop)
	{	
		std::cout << player;
		std::cout << "choose action:\n 1. mine\n 2. sell\n 3. craft\n 4. equip\n";
		std::string line;
		std::getline(std::cin, line);
		if (line == "mine" || line == "1")
			Mine(player);
		else if (line == "sell" || line == "2" || line == "sell all" || line == "sell everything")
			player.SellHotbar();
		else if (line.length() >= 5 && line.substr(0, 4) == "sell") {
			player.SellItem(line.substr(5, line.length()));
		}
		else if (line == "craft" || line == "3")
		{
			Craft(player);
		}
		else;

	}
}


// 46:11