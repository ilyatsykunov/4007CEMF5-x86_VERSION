#pragma once
#include <iostream>
#include <string> 

/* This class is for the moves the creeps can use */
class Moves
{
public:
	int moveID;
	std::string moveName;
	std::string moveType;
	std::string category;
	int power;
	int accuracy;
	int tier;

	Moves(int newMoveID, std::string newMoveName, std::string newMoveType, std::string NewCategory, int newPower, int newAccuracy, int newTier)
	{
		moveID = newMoveID;
		moveName = newMoveName;
		moveType = newMoveType;
		category = NewCategory;
		power = newPower;
		accuracy = newAccuracy;
		tier = newTier;
	}

	Moves()
	{

	}
	void setUp(int newMoveID, std::string newMoveName, std::string newMoveType, std::string NewCategory, int newPower, int newAccuracy, int newTier)
	{
		moveID = newMoveID;
		moveName = newMoveName;
		moveType = newMoveType;
		category = NewCategory;
		power = newPower;
		accuracy = newAccuracy;
		tier = newTier;
	}

	int getMoveID()
	{
		return moveID;
	}

	std::string getMoveName()
	{
		return moveName;
	}

	std::string getMoveType()
	{
		return moveType;
	}

	std::string getCategory()
	{
		return category;
	}

	int getPower()
	{
		return power;
	}

	int getAccuracy()
	{
		return accuracy;
	}

	int getTier()
	{
		return tier;
	}
};
