/// Item.h this is the controller for everything related to Items - their stats, buffs, price etc.
/// Author - Ilya Tsykunov
#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Creep.h"
#include "Trainer.h"
using namespace std;

//I.T. Base class for all items
class Item {
public:
	string name;
	float price;
	friend bool operator==(Item one, Item two);
	friend void operator<<(ostream& out, Item one);

	Item(string, float);
	Item();
	void addHealth();
};
//I.T. Item constructor
Item::Item(string name, float price) {
	this->name = name;
	this->price = price;
}
//A.G.
Item::Item() {}
//A.G.
void Item::addHealth() {}
//A.G.
bool operator==(Item one, Item two)
{
	return (one.name == two.name);
}
//A.G.
void operator<<(ostream& out, Item one)
{
	out << one.name;
}
//I.T. Base c,ass for potions 
class Potion : public Item {
public:
	Potion(string, float);
};
//I.T. Potion class constructor
Potion::Potion(string name, float price) : Item(name, price) {
}
//I.T. Health potion class
class HealthPotion : public Potion {
public:
	int addHealth;
	HealthPotion(string, float, int);
};
//I.T. Health potion class contstructor
HealthPotion::HealthPotion(string name, float price, int newAddHealth) : Potion(name, price) {
	addHealth = newAddHealth;
}
//I.T. Stat boosting potion for creeps class
class StatBoostingPotion : public Potion {
public:
	int boostAttack_Physical;
	int boostAttack_Magical;
	int boostDefence_Physical;
	int boostDefence_Magical;
	int boostCreepSpeed;
	StatBoostingPotion(string, float, int, int, int, int, int);
};
//I.T. Stat boosting potion for creeps constructor
StatBoostingPotion::StatBoostingPotion(string name, float price, int boostAttack_Physical, int boostAttack_Magical, int boostDefence_Physical, int boostDefence_Magical, int boostCreepSpeed) : Potion(name, price) {
	this->boostAttack_Physical = boostAttack_Physical;
	this->boostAttack_Magical = boostAttack_Magical;
	this->boostDefence_Physical = boostDefence_Physical;
	this->boostDefence_Magical = boostDefence_Magical;
	this->boostCreepSpeed = boostCreepSpeed;
}
//I.T. Reviving potion for creeps class
class RevivePotion : public Potion {
public:
	RevivePotion(string, float);
};
//I.T. Reviving potion for creeps class constructor
RevivePotion::RevivePotion(string name, float price) : Potion(name, price) {}

#endif
