/// Creep.h this is the controller for everything related to Creeps - their stats, combat etc.
/// Author - Ilya Tsykunov, Adam Gill, Paul Chessum
#ifndef CREEP_H
#define CREEP_H

#include <iostream>
#include <string>
#include <windows.h>
#include "trainer.h"
#include "Item.h"
#include "moves.h"
#include <fstream>
#include <sqlite3.h>
#include <libsqlite.hpp>
#include <stdlib.h>

using namespace std;

//I.T. The base class for the different types (In RP games those "Types" are called "Classes", hence the name) of creeps, it declares all of the variables those types all have
class CreepClass { 
public:
	//Base stats 
	int baseCreepHP;
	int baseCreepAttack_Physical;
	int baseCreepAttack_Magical;
	int baseCreepDefence_Physical;
	int baseCreepDefence_Magical;
	int baseCreepSpeed;

	//Level up stats
	int levelUpCreepHP;
	int levelUpCreepAttack_Physical;
	int levelUpCreepAttack_Magical;
	int levelUpCreepDefence_Physical;
	int levelUpCreepDefence_Magical;
	int levelUpCreepSpeed;

	int turnsToBleed = 0;
};
//I.T. One of the types of creeps, inherits from the base class "CreepClass".
class Mage : public CreepClass {
public:
	Mage()
	{
		//Base stats 
		baseCreepHP = 70;
		baseCreepAttack_Physical = 5;
		baseCreepAttack_Magical = 50;
		baseCreepDefence_Physical = 5;
		baseCreepDefence_Magical = 50;
		baseCreepSpeed = 5;

		//Level up stats 
		levelUpCreepHP = 5;
		levelUpCreepAttack_Physical = 0;
		levelUpCreepAttack_Magical = 10;
		levelUpCreepDefence_Physical = 2;
		levelUpCreepDefence_Magical = 10;
		levelUpCreepSpeed = 1;
	}
};
//I.T. One of the types of creeps, inherits from the base class "CreepClass".
class Priest : public CreepClass {
public:
	Priest()
	{
		//Base stats 
		baseCreepHP = 70;
		baseCreepAttack_Physical = 5;
		baseCreepAttack_Magical = 50;
		baseCreepDefence_Physical = 5;
		baseCreepDefence_Magical = 50;
		baseCreepSpeed = 8;

		//Level up stats
		levelUpCreepHP = 5;
		levelUpCreepAttack_Physical = 0;
		levelUpCreepAttack_Magical = 10;
		levelUpCreepDefence_Physical = 2;
		levelUpCreepDefence_Magical = 10;
		levelUpCreepSpeed = 1;
	}
};
//I.T. One of the types of creeps, inherits from the base class "CreepClass".
class Knight : public CreepClass {
public:
	Knight()
	{
		//Base stats 
		baseCreepHP = 100;
		baseCreepAttack_Physical = 50;
		baseCreepAttack_Magical = 5;
		baseCreepDefence_Physical = 50;
		baseCreepDefence_Magical = 5;
		baseCreepSpeed = 5;

		//Level up stats
		levelUpCreepHP = 5;
		levelUpCreepAttack_Physical = 10;
		levelUpCreepAttack_Magical = 0;
		levelUpCreepDefence_Physical = 10;
		levelUpCreepDefence_Magical = 1;
		levelUpCreepSpeed = 1;
	}
};
//I.T. One of the types of creeps, inherits from the base class "CreepClass".
class Assassin : public CreepClass {
public:
	Assassin()
	{
		//Base stats 
		baseCreepHP = 70;
		baseCreepAttack_Physical = 70;
		baseCreepAttack_Magical = 5;
		baseCreepDefence_Physical = 25;
		baseCreepDefence_Magical = 5;
		baseCreepSpeed = 10;

		//Level up stats
		levelUpCreepHP = 5;
		levelUpCreepAttack_Physical = 10;
		levelUpCreepAttack_Magical = 0;
		levelUpCreepDefence_Physical = 5;
		levelUpCreepDefence_Magical = 0;
		levelUpCreepSpeed = 1;
	}
};
//I.T. One of the types of creeps, inherits from the base class "CreepClass".
class Healer : public CreepClass {
public:
	Healer()
	{
		//Base stats 
		baseCreepHP = 100;
		baseCreepAttack_Physical = 5;
		baseCreepAttack_Magical = 25;
		baseCreepDefence_Physical = 25;
		baseCreepDefence_Magical = 25;
		baseCreepSpeed = 8;

		//Level up stats
		levelUpCreepHP = 5;
		levelUpCreepAttack_Physical = 0;
		levelUpCreepAttack_Magical = 10;
		levelUpCreepDefence_Physical = 5;
		levelUpCreepDefence_Magical = 10;
		levelUpCreepSpeed = 1;
	}
};
//Class for the creeps, stores their stats, their sprites and functions related to them - taking damage, healing, reviving, etc.
class Creep {
private:
	//Level up stats
	int levelUpCreepHP;
	int levelUpCreepAttack_Physical;
	int levelUpCreepAttack_Magical;
	int levelUpCreepDefence_Physical;
	int levelUpCreepDefence_Magical;
	int levelUpCreepSpeed;	
	int creepLevel;
	float creepExperience;

	// (A.G)
	bool isActive = false;
	std::string creepType;

	// (A.G)

public:
	//Stats
	string creepName;
	int creepHealthMax;
	int creepHealth;
	int creepAttack_Physical;
	int creepAttack_Magical;
	int creepDefence_Physical;
	int creepDefence_Magical;
	int creepSpeed;
	bool hasSprite;

	bool isAlive;
	bool isPlayable = true;
	int turnsToBleed = 0;

	Moves nextMove; // NEW 
	Moves activeMove; // OLD
	std::vector<std::string> creepVect;

	vector<Moves> creepMoves;
	void addBleeding(int);
	void bleed(WINDOW*);

	Creep() // (A.G)
	{
		// getSprite(creepName);
		creepName = "Testin";
		isPlayable = true;
		creepHealth = 500;
		creepSpeed = 50000;
		creepMoves = getStartingMoves();
	}
	Creep(std::string name) // (A.G)
	{
		getSprite(creepName);
		creepName = "Testin";
		isPlayable = true;
		creepHealth = 500;
		creepSpeed = 50000;
	}


	// (A.G) vv
	/*
	vector<std::string> getMoves()
	{
		std::vector<std::string> creepMoves;
		for (int i = 0; i < 4; i++)
		{
			creepMoves.push_back(moves[i]);
		}
		return creepMoves;
	}
	*/
	Creep(string, string, int, int, int, int, int, int);
	bool getActiveState();
	bool getFaintedStatus();
	void setActiveState(bool);
	bool attack(Creep&, int);
	bool getSprite(std::string name);
	void drawSprite(WINDOW*);
	void setNextMove(int);
	std::string getNextMove();
	void displayMoveInfo(WINDOW*, int);
	int nLearnedMoves();
	int getLevel();
	int getHealthStat();
	int getPhyAtkStat();
	int getPhyDefStat();
	int getMagAtkStat();
	int getMagDefStat();
	int getSpeedStat();
	float getHealth();
	std::string getType();
	vector<Moves> getStartingMoves();
	void displayCreepInfo(WINDOW*);
	// (A.G) ^^

	void Awaken();
	void Death();
	void Revive();
	void Defence_Magical(int);
	bool ChangeHealth(int);
	void Attack_Physical(Creep);
	void Attack_Magical(Creep);
	void Defence_Physical(int);
	void CreepLevelUp();
	void ChangeExperience(float);


};

//Creep constructor. Takes in values from the database and sets stats according to the class it has
Creep::Creep(string newCreepName, string newCreepClass, int newCreepHealthMax, int newCreepAttack_Physical, int newCreepAttack_Magical, int newCreepDefence_Physical, int newCreepDefence_Magical, int newCreepSpeed) {
	creepName = newCreepName;
	creepType = newCreepClass;
	if (newCreepClass == "Mage") {
		Mage creepClass;
		creepHealthMax = creepClass.baseCreepHP;
		creepAttack_Physical = creepClass.baseCreepAttack_Physical;
		creepAttack_Magical = creepClass.baseCreepAttack_Magical;
		creepDefence_Physical = creepClass.baseCreepDefence_Physical;
		creepDefence_Magical = creepClass.baseCreepDefence_Magical;
		creepSpeed = creepClass.baseCreepSpeed;
		levelUpCreepHP = creepClass.levelUpCreepHP;
		levelUpCreepAttack_Physical = creepClass.levelUpCreepAttack_Physical;
		levelUpCreepAttack_Magical = creepClass.levelUpCreepAttack_Magical;
		levelUpCreepDefence_Physical = creepClass.levelUpCreepDefence_Physical;
		levelUpCreepDefence_Magical = creepClass.levelUpCreepDefence_Magical;
		levelUpCreepSpeed = creepClass.levelUpCreepSpeed;
	}
	else if (newCreepClass == "Priest") {
		Priest creepClass;
		creepHealthMax = creepClass.baseCreepHP;
		creepAttack_Physical = creepClass.baseCreepAttack_Physical;
		creepAttack_Magical = creepClass.baseCreepAttack_Magical;
		creepDefence_Physical = creepClass.baseCreepDefence_Physical;
		creepDefence_Magical = creepClass.baseCreepDefence_Magical;
		creepSpeed = creepClass.baseCreepSpeed;
		levelUpCreepHP = creepClass.levelUpCreepHP;
		levelUpCreepAttack_Physical = creepClass.levelUpCreepAttack_Physical;
		levelUpCreepAttack_Magical = creepClass.levelUpCreepAttack_Magical;
		levelUpCreepDefence_Physical = creepClass.levelUpCreepDefence_Physical;
		levelUpCreepDefence_Magical = creepClass.levelUpCreepDefence_Magical;
		levelUpCreepSpeed = creepClass.levelUpCreepSpeed;
	}
	else if (newCreepClass == "Knight") {
		Knight creepClass;
		creepHealthMax = creepClass.baseCreepHP;
		creepAttack_Physical = creepClass.baseCreepAttack_Physical;
		creepAttack_Magical = creepClass.baseCreepAttack_Magical;
		creepDefence_Physical = creepClass.baseCreepDefence_Physical;
		creepDefence_Magical = creepClass.baseCreepDefence_Magical;
		creepSpeed = creepClass.baseCreepSpeed;
		levelUpCreepHP = creepClass.levelUpCreepHP;
		levelUpCreepAttack_Physical = creepClass.levelUpCreepAttack_Physical;
		levelUpCreepAttack_Magical = creepClass.levelUpCreepAttack_Magical;
		levelUpCreepDefence_Physical = creepClass.levelUpCreepDefence_Physical;
		levelUpCreepDefence_Magical = creepClass.levelUpCreepDefence_Magical;
		levelUpCreepSpeed = creepClass.levelUpCreepSpeed;
	}
	else if (newCreepClass == "Assassin") {
		Assassin creepClass;
		creepHealthMax = creepClass.baseCreepHP;
		creepAttack_Physical = creepClass.baseCreepAttack_Physical;
		creepAttack_Magical = creepClass.baseCreepAttack_Magical;
		creepDefence_Physical = creepClass.baseCreepDefence_Physical;
		creepDefence_Magical = creepClass.baseCreepDefence_Magical;
		creepSpeed = creepClass.baseCreepSpeed;
		levelUpCreepHP = creepClass.levelUpCreepHP;
		levelUpCreepAttack_Physical = creepClass.levelUpCreepAttack_Physical;
		levelUpCreepAttack_Magical = creepClass.levelUpCreepAttack_Magical;
		levelUpCreepDefence_Physical = creepClass.levelUpCreepDefence_Physical;
		levelUpCreepDefence_Magical = creepClass.levelUpCreepDefence_Magical;
		levelUpCreepSpeed = creepClass.levelUpCreepSpeed;
	}
	else if (newCreepClass == "Healer") {
		Healer creepClass;
		creepHealthMax = creepClass.baseCreepHP;
		creepAttack_Physical = creepClass.baseCreepAttack_Physical;
		creepAttack_Magical = creepClass.baseCreepAttack_Magical;
		creepDefence_Physical = creepClass.baseCreepDefence_Physical;
		creepDefence_Magical = creepClass.baseCreepDefence_Magical;
		creepSpeed = creepClass.baseCreepSpeed;			levelUpCreepHP = creepClass.levelUpCreepHP;
		levelUpCreepAttack_Physical = creepClass.levelUpCreepAttack_Physical;
		levelUpCreepAttack_Magical = creepClass.levelUpCreepAttack_Magical;
		levelUpCreepDefence_Physical = creepClass.levelUpCreepDefence_Physical;
		levelUpCreepDefence_Magical = creepClass.levelUpCreepDefence_Magical;
		levelUpCreepSpeed = creepClass.levelUpCreepSpeed;
	}
	creepHealthMax += newCreepHealthMax;
	creepAttack_Physical += newCreepAttack_Physical;
	creepAttack_Magical += newCreepAttack_Magical;
	creepDefence_Physical += creepDefence_Physical;
	creepDefence_Magical += creepDefence_Magical;
	creepSpeed += newCreepSpeed;

	creepHealth = creepHealthMax;
	creepLevel = 1;
	creepExperience = 0.0;

	isPlayable = true;
	creepMoves = getStartingMoves();
	getSprite(creepName);

}

std::string Creep::getType()
{
	return creepType;
}
//I.T. if creep is at 0 health
void Creep::Awaken() {
	if (isPlayable == false) {
		isPlayable = true;
		creepHealth = creepHealthMax / 2;
	}
}

void Creep::Death() 
{
	creepHealth = 0;
	isPlayable = false;	
}
//I.T. obsolete function for when creep is dead
void Creep::Revive() {
	if (isAlive == false && isPlayable == false) {
		isAlive = true;
		isPlayable = true;
		creepHealth = creepHealthMax / 2;
	}
}
//I.T. obsolete function for counting damage dealt with magic
void Creep::Defence_Magical(int damage) {
	if (isPlayable == true) {
		float damageDealt = ((2 * creepLevel / 2 + 2) * 1 /*Modifier*/ * damage / creepDefence_Magical + 2) / 50 * 1 /*Modifier*/;
	}
}
//I.T. function for adding and taking away health. Creep dies if health is at 0
bool Creep::ChangeHealth(int newHealth) {
	if (isPlayable == true) {
		/* 
		if (newHealth > 0) {
			if (creepHealth + newHealth <= creepHealthMax) {
				creepHealth += newHealth;
			}
			else {
				creepHealth = creepHealthMax;
			}
		}
		*/
		if (creepHealth + newHealth > 0) {
			creepHealth += newHealth;
		}
		else
		{
			creepHealth = 0;
			Death();
			return true;
		}		
	}
	return false;
}
//I.T. obsolete function for physical attack
void Creep::Attack_Physical(Creep enemy) {
	if (isPlayable == true) {
		enemy.Defence_Physical(creepAttack_Physical);
	}
}
//I.T. obsolete function for magical attack
void Creep::Attack_Magical(Creep enemy) {
	if (isPlayable == true) {
		enemy.Defence_Magical(creepAttack_Magical);
	}
}
//I.T. obsolete function for counting damage dealt with physical
void Creep::Defence_Physical(int damage) {
	if (isPlayable == true) {
		float damageDealt = ((2 * creepLevel / 2 + 2) * 1 /*Modifier*/ * damage / creepDefence_Physical + 2) / 50 * 1 /*Modifier*/;
	}
}
//I.T. function for leveling up creeps and updating their max stats
void Creep::CreepLevelUp() {
	if (isPlayable == true) {
		creepLevel += 1;
		creepHealthMax += levelUpCreepHP;
		creepAttack_Physical += levelUpCreepAttack_Physical;
		creepAttack_Magical += levelUpCreepAttack_Magical;
		creepDefence_Physical += levelUpCreepDefence_Physical;
		creepDefence_Magical += levelUpCreepDefence_Magical;
		creepSpeed += levelUpCreepSpeed;
	}
}
//I.T. function for adding experience to creeps and leveling up
void Creep::ChangeExperience(float newExperience) {
	//amout of experience needed to level up
	float maxLevelExperience = creepLevel * 50;

	if (creepExperience + newExperience >= maxLevelExperience) {
		float experienceLeft = (creepExperience + newExperience) - maxLevelExperience;
		CreepLevelUp();
		ChangeExperience(experienceLeft);
	}
	else {
		creepExperience += newExperience;
	}
}

/* TESTING FUNCTION Returns the move to be used next (A.G) */
std::string Creep::getNextMove()
{
	return nextMove.getMoveName();
}

/* Assigns the first 2 moves of it's type to the creep */
vector<Moves> Creep::getStartingMoves()
{
	vector<Moves> moves;
	sqlite::sqlite database("./db_files/Moves.db");
	auto cur = database.get_statement();

	cur->set_sql("SELECT MoveID, MoveName, MoveType, Category, Power, Accuracy, Tier FROM moves WHERE MoveType = ? AND Tier = 1 ORDER BY MoveID");
	cur->prepare();
	cur->bind(1, creepType);

	while (cur->step())
	{
		Moves creepMove(cur->get_int(0), cur->get_text(1), cur->get_text(2), cur->get_text(3), cur->get_int(4), cur->get_int(5), cur->get_int(6));
		moves.push_back(creepMove);
	}
	return moves;
}


/* Get's the creeps current health */
float Creep::getHealth()
{
	return creepHealth;
}

/* Get's the creep's level */
int Creep::getLevel()
{
	return creepLevel;
}

/* Get's the creep's health stat */
int Creep::getHealthStat()
{
	return creepHealthMax;
}

/* Get's the creep's physical attack stat */
int Creep::getPhyAtkStat()
{
	return creepAttack_Physical;
}

/* Get's the creep's physical defence stat */
int Creep::getPhyDefStat()
{
	return creepDefence_Physical;
}

/* Get's the creep's magical attack stat */
int Creep::getMagAtkStat()
{
	return creepAttack_Magical;
}

/* Get's the creep's magical defence stat */
int Creep::getMagDefStat()
{
	return creepDefence_Magical;
}

/* Get's the creep's speed stat */
int Creep::getSpeedStat()
{
	return creepSpeed;
}

/* Returns the number of moves currently learned by the creep (A.G) */
int Creep::nLearnedMoves()
{
	return creepMoves.size();
}

/* Grabs displays the given moves information in a window next to the player options  (A.G) */
void Creep::displayMoveInfo(WINDOW* win, int option)
{
	wclear(win);
	wrefresh(win);
	box(win, 0, 0);
	Moves move_two;
	//try
	//{		
	sqlite::sqlite database("./db_files/Moves.db");
	auto cur = database.get_statement();
	cur->set_sql("SELECT MoveID, MoveName, MoveType, Category, Power, Accuracy, Tier FROM moves WHERE MoveID = ?;");
	cur->prepare();
	cur->bind(1, option + 1);
	Moves move_one;

	while (cur->step())
	{
		move_one.setUp(cur->get_int(0), cur->get_text(1), cur->get_text(2), cur->get_text(3), cur->get_int(4), cur->get_int(5), cur->get_int(6));
	}

	vector<std::string> stats = { "ID: ", "Move Name: ", "Move Type: ", "Move Category: ", "Move Power: ", "Move Accuracy: ", "Tier: " };
	std::string outt;

	outt = stats[0] + to_string(move_one.getMoveID());
	mvwprintw(win, 1, 1, outt.c_str());
	outt = stats[1] + move_one.getMoveName();
	mvwprintw(win, 3, 1, outt.c_str());
	outt = stats[2] + move_one.getMoveType();
	mvwprintw(win, 5, 1, outt.c_str());
	outt = stats[3] + move_one.getCategory();
	mvwprintw(win, 7, 1, outt.c_str());
	outt = stats[4] + to_string(move_one.getPower());
	mvwprintw(win, 9, 1, outt.c_str());
	outt = stats[5] + to_string(move_one.getAccuracy());
	mvwprintw(win, 11, 1, outt.c_str());
	outt = stats[6] + to_string(move_one.getTier());
	mvwprintw(win, 13, 1, outt.c_str());
	wrefresh(win);
	//}
	/* catch (sqlite::exception e)
	{
		cerr << e.what() << endl;
	}*/
	wrefresh(win);
}

/* Displays the creeps stats, when the player is switching their creep */
void Creep::displayCreepInfo(WINDOW* win)
{
	wclear(win);
	wrefresh(win);
	box(win, 0, 0);

	vector<std::string> stats = { "Health: ", "Physical Attack: ", "Physical Defence: ", "Magical Attack: ", "Magical Defence: ", "Speed: "};
	std::string outt;
	outt = stats[0] + to_string(creepHealthMax);
	mvwprintw(win, 1, 1, outt.c_str());
	outt = stats[1] + to_string(creepAttack_Physical);
	mvwprintw(win, 2, 1, outt.c_str());
	outt = stats[2] + to_string(creepDefence_Physical);
	mvwprintw(win, 3, 1, outt.c_str());
	outt = stats[3] + to_string(creepAttack_Magical);
	mvwprintw(win, 4, 1, outt.c_str());
	outt = stats[4] + to_string(creepDefence_Magical);
	mvwprintw(win, 5, 1, outt.c_str());
	outt = stats[5] + to_string(creepSpeed);
	mvwprintw(win, 6, 1, outt.c_str());

	wrefresh(win);
}

/* Gets the creep sprite from the file using the name of the creep (A.G) */
bool Creep::getSprite(std::string name)
{
	std::ifstream file;
	file.open("../4007CEM_F5/text_files/creep_sprites.txt", std::ios::in);
	std::string line;
	hasSprite = false;
	while (file)
	{
		std::getline(file, line);
		if (line == name)
		{
			hasSprite = true;
			for (int i = 1; i < 8; i++)
			{
				std::getline(file, line);
				std::replace(line.begin(), line.end(), 'X', ' ');
				creepVect.push_back(line);
			}
			return true;
		}
	} 

	file.close();
	refresh();
	return false;
}

/* Draws the sprite to the creep window (A.G) */
void Creep::drawSprite(WINDOW* win)
{
	if (creepVect.size() != 0)
	{
		for (int i = 0; i < 7; i++)
		{
			mvwprintw(win, i + 2, 1, creepVect[i].c_str());
		}
	}
	wrefresh(win);
}

/* Passes in 0-4 of the move the trainer has chosen to play in their turn (A.G) */
void Creep::setNextMove(int chosenMove)
{
	nextMove = creepMoves[chosenMove];
}

/* Checks if the creep is currently in play (A.G) */
bool Creep::getActiveState()
{
	return isActive;
}

/* Used to check if the Creep has fainted or not (A.G) */
bool Creep::getFaintedStatus()
{
	return !isPlayable;
}

/* Used to change the creep in play (A.G) */
void Creep::setActiveState(bool active)
{
	isActive = active;
}

/* Attacks the target creep with the currently active set move (A.G) */

//P.C

void Creep::addBleeding(int turns)
{
	turnsToBleed = turnsToBleed + turns;
}

void Creep::bleed(WINDOW* win)
{
	if (turnsToBleed > 0)
	{
		creepHealth = (creepHealth - (creepHealthMax / 10));
		//display this to the window
		turnsToBleed = turnsToBleed - 1;
	}
}
bool Creep::attack(Creep& target, int damage)
{
	if (nextMove.getPower() == 0)
	{
		if (nextMove.getMoveName() == "Joust")
		{
			int random = rand() % 0 + 1;
			if (random == 0)
			{
				creepHealth = creepHealth / 2;
			}
			else
			{
				target.creepHealth = target.creepHealth / 2;
			}
		}
		if (nextMove.getMoveName() == "Bandage")
		{
			creepHealth = creepHealth + 10;
		}
		if (nextMove.getMoveName() == "Leeches")
		{
			target.addBleeding(2);
			//bleeding damage needs to be implemented
		}
		if (nextMove.getMoveName() == "Biohazard")
		{
			target.addBleeding(4);
		}
		if (nextMove.getMoveName() == "Steroids")
		{
			creepDefence_Physical = creepDefence_Physical + 20;
			creepAttack_Physical = creepAttack_Physical + 20;
		}
		if (nextMove.getMoveName() == "SecretPotion")
		{
			int random = rand() % 0 + 1;
			if (random == 0)
			{
				creepHealth = creepHealthMax;
			}
		}
		if (nextMove.getMoveName() == "Charitable")
		{
			creepDefence_Magical = creepDefence_Magical + 20;
			creepAttack_Magical = creepAttack_Magical + 20;
		}
		if (nextMove.getMoveName() == "Charitable")
		{
			target.addBleeding(6);
		}

	}
	else
	{
		int random = rand() % 1 + 100;
		if (random >= activeMove.getAccuracy());
		{
			bool fainted = target.ChangeHealth(-damage);
			if (fainted)
			{
				Death();
				return true;
			}
		}		
	}
}

#endif // !CREEP_H
