#include "Player.h"
int Player::ValueInRange1To(int x) {
	return (rand() % x) + 1;
}
Player::Player(const Player& other)
{
    this->money = other.money;
    this->tool = other.tool;
    hotb_size = other.hotb_size;
    if (hotb_size != 0)
    {
        hotbar = new Treasure[hotb_size];
        for (int i = 0; i < hotb_size; i++)
            hotbar[i] = other.hotbar[i];
    }
}

// operator= atribuire prin copiere
Player& Player::operator=(const Player& other)
{
    this->money = other.money;
    this->tool = other.tool;
    if (this != &other)
    {
        hotb_size = other.hotb_size;
        delete[] hotbar;
        hotbar = new Treasure[hotb_size];
        for (int i = 0; i < hotb_size; i++)
            hotbar[i] = other.hotbar[i];
    }
    return *this;
}

// constructor de mutare
Player::Player(Player&& other) noexcept : hotb_size{ other.hotb_size }, hotbar{ other.hotbar }, tool{ other.tool }, money{other.money}
{
    other.hotb_size = -1;
    other.money = -1;
    other.hotbar = nullptr;
}

// operator= atribuire prin mutare
Player& Player::operator=(Player&& other) noexcept
{
    if (this != &other)
    {
        this->money = other.money;
        this->tool = other.tool;
        this->hotb_size = other.hotb_size;
        delete[] this->hotbar; // not sure I should delete this but probably yes
        this->hotbar = other.hotbar;
        other.hotb_size= -1;
        other.money = -1;
        other.hotbar = nullptr;
    }
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Player& player) {
    os << "hotbar size = " << player.hotb_size << "\n";
    for (int i = 0; i < player.hotb_size; i++) {
        if (player.hotbar[i].GetCount() == 0)
            break;
        if (i != player.hotb_size - 1 and player.hotbar[i + 1].GetCount() != 0)
            os << player.hotbar[i].GetCount() << " x " << player.hotbar[i].GetName() << " = " << player.hotbar[i].GetValue() << ", ";
        else
            os << player.hotbar[i].GetCount() << " x " << player.hotbar[i].GetName() << " = " << player.hotbar[i].GetValue() << "\n";
    }
    os << player.money << " $\n";
    return os;
}

Player::Player()
{
    tool = Tool();
    money = 0;
    hotb_size = 3;
    hotbar = new Treasure[hotb_size];
	std::cout << "created a player with " << hotb_size << " slots of hotbar for treasure!\n";
}

void Player::AddTreasure(Treasure treasureitem) {
    bool ok = 0;
    for (int i = 0; i < hotb_size; i++) {
        if (hotbar[i].GetName() == treasureitem.GetName())
        {
            hotbar[i] = std::move(hotbar[i] + treasureitem);
            printf("+%d %s", treasureitem.GetCount(), treasureitem.GetName().c_str());
            ok = 1;
            break;
        }
        else
            if (hotbar[i].GetName() == "")
            {
                hotbar[i] = std::move(treasureitem);
                printf("+%d %s", treasureitem.GetCount(), treasureitem.GetName().c_str());
                ok = 1;
                break;
            }
    }
    if (!ok) {
        std::cout << "\n\n!hotbar full!\n" << treasureitem.GetName() << " lost\n";
    }
    tool.Wear();
}

void Player::UpgradeHotbar() {
    Treasure* hotbar_ = new Treasure[++this->hotb_size];
    for (int i = 0; i < this->hotb_size - 1; i++)
        hotbar_[i] = this->hotbar[i];
    delete[] this->hotbar;
    this->hotbar = hotbar_;
    std::cout << "upgraded hotbar!\n";
}

void Player::SellHotbar() {
    int k = 0;
    for (int i = 0; i < this->hotb_size; i++)
        if (hotbar[i].GetName() == "")
            break;
        else {
            this->money += hotbar[i].GetValue();
            k++;
            hotbar[i] = Treasure();
        }
}

void Player::SellItem(std::string item_name) {
    bool ok = 0;
    for (int i = 0; i < this->hotb_size; i++) {
        if (hotbar[i].GetName() == "")
            break;
        if (hotbar[i].GetName() == item_name) {
            this->money += hotbar[i].GetValue();
            if (i != hotb_size - 1) {
                ok = 1;
            }
            else{
                hotbar[i] = Treasure();
                break;
            }
        }
        if (ok && i != hotb_size - 1) {
            hotbar[i] = hotbar[i + 1];
        }
        else if (ok && i == hotb_size - 1) {
            hotbar[i] = Treasure();
        }
    }
}

void Player::PrintHotbar() {
    for (int i = 0; i < hotb_size; i++) {
        std::cout << i + 1 << ". ";
        hotbar[i].PrintTreasure();
    }
}

void Player::UpgradeTool(float efficiency, int durability) {
    this->tool.Upgrade(efficiency, durability);
}
int Player::ToolEfficiency() {
    return this->tool.GetEfficiency();
}

Player::~Player() {
	delete[] hotbar;
};