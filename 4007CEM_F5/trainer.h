/// Trainer.h this is the controller for everything related to Trainers - their creeps, inventory etc.
/// Author - Ilya Tsykunov, Adam
#ifndef TRAINER_H
#define TRAINER_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "Creep.h"
#include "Item.h"
#include <time.h>

using namespace std;

//Class for trainers - the people that control creeps
class Trainer {
private:
	string trainerName;
	float trainerMoney;
	int trainerScore;
	bool whitedOut; // whether the player has usable creeps left
public:
	//inventory
	vector<Item> trainerInventory;
	int trainerHealthPotions;
	int trainerAwakeningPotions;
	int trainerStatBoostingPotions;
	//Battle
	int trainerHealthDebuff;
	int faintedCreeps;
	int trainerDebuffTurnsLeft;
	bool trainerActive;
	int activeCreepNum;
	Creep targetCreep;
	Item targetItem;
	vector<Creep> trainerCreeps;

	//I.T.
	Trainer(string, Creep&, Creep&, Creep&);
	//A.G.
	Trainer();
	//A.G.
	Trainer(float);
	//A.G.
	Trainer(std::string);


	//I.T.
	void SelectActiveCreep(int);
	//I.T.
	void UseHealthPotion();
	//I.T.
	void UseAwakeningPotion();
	//I.T.
	void UseStatBoostingPotion();
	//I.T.
	int GetScore();
	//I.T.
	void AddScore(int);

	//A.G.
	float getTrainerMoney();
	//A.G.
	void Buy(Item);
	//A.G.
	void Sell(Item);
	//A.G.
	void showInventory();
	//A.G.
	bool checkWhiteOut();
	//A.G.
	vector<Creep> giveRandomCreeps();


	//I.T.

};
//I.T. Constructor for trainer class adapted for SQL data 
Trainer::Trainer(string newName, Creep &newCreep1, Creep &newCreep2, Creep &newCreep3) {
	trainerName = newName;
	trainerCreeps.push_back(newCreep1);
	trainerCreeps.push_back(newCreep2);
	trainerCreeps.push_back(newCreep3);
	trainerMoney = 0;
	trainerInventory = {};
	trainerScore = 0;
	whitedOut = false;
}
//I.T. chose the currently played creep
void Trainer::SelectActiveCreep(int newActiveCreepNum) {
	activeCreepNum = newActiveCreepNum;
}
//I.T. Apply health potion to a creep
void Trainer::UseHealthPotion() {
	Creep &targetCreep = trainerCreeps[activeCreepNum];
	targetCreep.ChangeHealth(50);
	trainerHealthPotions--;
}
//I.T. Awaken creep by applying an awakening potion
void Trainer::UseAwakeningPotion() {
	Creep &targetCreep = trainerCreeps[activeCreepNum];
	targetCreep.Awaken();
	trainerAwakeningPotions--;
}
//I.T. Boost creep's stats by applying a stat boosting potion
void Trainer::UseStatBoostingPotion() {
	Creep &targetCreep = trainerCreeps[activeCreepNum];
	float percentage = 0.25;
	targetCreep.creepAttack_Physical += percentage * targetCreep.creepAttack_Physical;
	targetCreep.creepAttack_Magical += percentage * targetCreep.creepAttack_Magical;
	targetCreep.creepDefence_Physical += percentage * targetCreep.creepDefence_Physical;
	targetCreep.creepDefence_Magical += percentage * targetCreep.creepDefence_Magical;
	targetCreep.creepSpeed += percentage * targetCreep.creepSpeed;
	trainerStatBoostingPotions--;
}
//I.T.
int Trainer::GetScore() {
	return trainerScore;
}
//I.T. add score to trainer for winning battle
void Trainer::AddScore(int newScore) {
	if (newScore > 0) {
		trainerScore += newScore;
	}
}

/* (A.G) */
bool Trainer::checkWhiteOut()
{
	return whitedOut;
}

/* Called by the constructor to get the default creeps into their inventory */
vector<Creep> Trainer::giveRandomCreeps()
{
	vector<Creep> trainerCreeps;

	sqlite::sqlite database("./db_files/Moves.db");
	auto cur = database.get_statement();
	cur->set_sql("SELECT Creep_Name, Creep_Class, Creep_Attack_Physical, Creep_Attack_Magical, Creep_Defence_Physical, Creep_Defence_Magical, Creep_Speed FROM creeps WHERE Creep_ID = 1 OR Creep_ID = 2 OR Creep_ID = 3");
	cur->prepare();
	//cur->bind(1, 1);	
		
	while (cur->step())
	{
		Creep creep_test(cur->get_text(0), cur->get_text(1), cur->get_int(2), cur->get_int(3), cur->get_int(4), cur->get_int(5), cur->get_int(6), cur->get_int(7));
		trainerCreeps.push_back(creep_test);
	}
	return trainerCreeps;
}


float Trainer::getTrainerMoney()
{
	return trainerMoney;
}
Trainer::Trainer()
{
	trainerCreeps = giveRandomCreeps();
	whitedOut = false;
	faintedCreeps = 0;
}

Trainer::Trainer(std::string name)
{
	trainerName = name;
	whitedOut = false;
}
Trainer::Trainer(float money)
{
	whitedOut = false;
	trainerMoney = money;
}
void Trainer::Buy(Item bItem)
{
	trainerInventory.push_back(bItem);
	trainerMoney -= bItem.price;
}
void Trainer::Sell(Item sItem)
{
	auto it = find(trainerInventory.begin(), trainerInventory.end(), sItem);
	if (it != trainerInventory.end())
	{
		trainerMoney += sItem.price;
		trainerInventory.erase(it);
	}
}

void Trainer::showInventory() // TO BE ADAPTED FOR PDCURSES
{
	for (int i = 0; i < trainerInventory.size(); i++)
	{
		cout << trainerInventory[i].name << endl;
	}
}

#endif

