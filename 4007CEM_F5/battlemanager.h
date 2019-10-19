/// Battlemanager.h - the class for managing the battles between two trainers. Provides both interface and 
/// Author - Adam, Ilya Tsykunov
#pragma once
#include "Trainer.h"
#include "Creep.h"
#include <vector>
class BattleManager
{
private:
	// (A.G) - BEGINNING
	WINDOW* playerOptions = newwin(7, 45, LINES - 8, 1);
	WINDOW* playerStatusBar = newwin(3, 45, (LINES - 10), 1);
	WINDOW* playerCreep = newwin(9, 45, LINES - 19, 1);
	WINDOW* enemyStatusBar = newwin(3, 45, 0, COLS - 45);
	WINDOW* enemyCreep = newwin(9, 45, 3, COLS - 45);
	WINDOW* changeCreeps = newwin(9, 20, LINES - 10, 47);
	WINDOW* statusWindow = newwin(9, 40, 0, 1);
	WINDOW* creepInfo = newwin(9, 25, LINES - 10, 68);
	bool gameOver = false;
	// (A.G) - END

public:
	Trainer trainer1;
	Trainer trainer2;
	std::vector<Creep> creepAttackList;

	int highlight = 0;
	BattleManager(vector<Item> playerInventory) // Default Constructor - Adam
	{
		trainer1.trainerInventory = playerInventory;

		refresh();
		box(playerOptions, 0, 0);
		box(playerStatusBar, 0, 0);
		box(playerCreep, 0, 0);
		box(enemyStatusBar, 0, 0);
		box(enemyCreep, 0, 0);
		box(changeCreeps, 0, 0);
		box(statusWindow, 0, 0);
		drawPlayerOptions(playerOptions, highlight);
		drawStatusBar(trainer1, playerStatusBar);
		drawStatusBar(trainer2, enemyStatusBar);
		drawCreep(trainer1, playerCreep);
		drawCreep(trainer2, enemyCreep);

		trainer1.trainerCreeps[0].setActiveState(true);
		trainer2.trainerCreeps[0].setActiveState(true);
	}
	BattleManager(Trainer newTrainer1, Trainer newTrainer2) {
		trainer1 = newTrainer1;
		trainer2 = newTrainer2;

		// Merging code - Adam
		refresh();	
		box(playerOptions, 0, 0);
		box(playerStatusBar, 0, 0);
		box(playerCreep, 0, 0);
		box(enemyStatusBar, 0, 0);
		box(enemyCreep, 0, 0);
		drawPlayerOptions(playerOptions, highlight);
		drawStatusBar(trainer1, playerStatusBar);
		drawStatusBar(trainer2, enemyStatusBar);
		drawCreep(trainer1, playerCreep);
		drawCreep(trainer2, enemyCreep);
		// Merging code - Adam

	}

	// Drawing the screen (A.G) - BEGINNING
	void drawPlayerOptions(WINDOW*, int);
	void drawStatusBar(Trainer&, WINDOW*);
	void drawCreep(Trainer&, WINDOW*);
	void drawChangeCreepWindow(WINDOW*, int);
	int fightOptions(WINDOW*);
	int drawFightOptions(WINDOW*, int);
	int playerTurn();
	int EnemyTurn(); //I.T.
	int changeCreep();
	int endGame(); 
	int playerChoice(int highlight);
	bool endTurn(int, int);
	void updateDamageInformation(WINDOW*, float);
	void damageDiagnostics(WINDOW*, vector<float>);
	int waitEnterKey(WINDOW*);
	int displayDamage(WINDOW*, int, bool);
	// (A.G) - END
	int GameLoop();
};


/* ROOT FUNCTION. Handles the 3 main stages of each turn (A.G)*/
int BattleManager::GameLoop()
{
	int highlight = 0;
	while (gameOver == false || trainer2.checkWhiteOut())
	{
		int playerAction = playerTurn(); /* 0 - 3 is index of move. Should have 4 identify an item usage and 5 a change of creep */
		int enemyAction = EnemyTurn(); /* 0 - 3 is index of move. Should have 4 identify an item usage and 5 a change of creep */
		gameOver = endTurn(playerAction, enemyAction);
	}
	if (gameOver == false || trainer2.checkWhiteOut()) {
		return endGame();
	}
	
}

/* ROOT FUNCTION. Returns 0 - 3 of the move the player wishes to move. Handles changing creep and using items, 5 is changing creeps, 6 is bag, 7 is run (A.G) */
int BattleManager::playerTurn()
{
	highlight = 0;
	int choice = playerChoice(highlight);

	switch (choice)
	{
	case 0: // Fight 
	{
		int move = fightOptions(playerOptions);
		trainer1.trainerCreeps[trainer1.activeCreepNum].setNextMove(move);
		return move;
		break;
	}
	case 1: // Change creeps
	{
		drawChangeCreepWindow(changeCreeps, 0);
		int option = changeCreep();
		trainer1.activeCreepNum = option;
		//mvwaddstr(playerCreep, 3, 15, trainer1.trainerCreeps[option].creepName.c_str());
		drawCreep(trainer1, playerCreep);
		wrefresh(playerCreep);
		return 5;
		break;
	}
	case 2: // Bag
		return 6;
		break;
	case 3: // Run
		return 7;
		break;
	}
}

/* ROOT FUNCTION Simulates the AI taking their turn */
int BattleManager::EnemyTurn() //I.T.
{

	int choice;
	Creep &playerCreep = trainer1.trainerCreeps[trainer1.activeCreepNum];
	Creep &enemyCreep = trainer2.trainerCreeps[trainer2.activeCreepNum];
	int playerTotalStats = enemyCreep.creepAttack_Physical + enemyCreep.creepAttack_Magical + enemyCreep.creepDefence_Physical + enemyCreep.creepDefence_Magical + enemyCreep.creepSpeed;
	int enemyTotalStats = playerCreep.creepAttack_Physical + enemyCreep.creepAttack_Magical + enemyCreep.creepDefence_Physical + enemyCreep.creepDefence_Magical + enemyCreep.creepSpeed;

	//if creep is dead - revive it
	if (enemyCreep.isPlayable == false && trainer2.trainerAwakeningPotions > 0) {
		trainer2.UseAwakeningPotion();
		return 4;
	}
	//If creep is dead - chose new creep
	else if (enemyCreep.isPlayable == false && trainer2.trainerAwakeningPotions == 0) {
		for (int i = 0; i < 3; i++) {
			if (trainer2.trainerCreeps[i].isPlayable == true) {
				trainer2.activeCreepNum = i;
				Creep &enemyCreep = trainer2.trainerCreeps[trainer2.activeCreepNum];
				return 5;
			}
		}
	}
	//if health is low
	else if (enemyCreep.creepHealth <= (enemyCreep.creepHealthMax / 100 * 30) && trainer2.trainerHealthPotions > 0) {
		trainer2.UseHealthPotion();
		return 4;
	}
	//Use stat boosting potion if needed
	else if (enemyTotalStats <= playerTotalStats && trainer2.trainerStatBoostingPotions > 0) {
		trainer2.UseStatBoostingPotion();
		return 4;
	}
	//if enemy creep is debuffed dont use debuff moves
	//else use any attack with most damage
	else {
		int bestPower = 0;
		int percentage = 0;
		int bestOption;
		for (int i = 0; i < 3; i++) {
			Moves &currentMove = enemyCreep.creepMoves[i];
			int newPercentage = rand() % 51;
			if (currentMove.getPower() > bestPower) {
				newPercentage += 30;
			}
			if (newPercentage > percentage) {
				percentage = newPercentage;
				bestPower = currentMove.getPower();
				bestOption = i;
			}
		}
		if (bestOption < 4)
			enemyCreep.setNextMove(bestOption);
		return bestOption;
	}
}

/* ROOT FUNCTION Calculates the damage, and applies effects of the moves */
bool BattleManager::endTurn(int playerAction, int enemyAction)
{
	float damage;
	bool adamtesting = true;
	vector<Creep> battleQueue;
	Creep playerActiveCreep;
	Creep enemyActiveCreep;
	float level, power, attack, defence, modifier;
	std::string category;

	enemyActiveCreep = trainer2.trainerCreeps[trainer2.activeCreepNum];
	playerActiveCreep = trainer1.trainerCreeps[trainer1.activeCreepNum];

	/* Puts the creeps into the order they will go in, if it's below 5 the player chose a move to use and not an item or change creep */
	if (playerAction < 5)
	{
		if (playerActiveCreep.creepSpeed >= enemyActiveCreep.creepSpeed)
		{
			battleQueue.push_back(playerActiveCreep);
			battleQueue.push_back(enemyActiveCreep);
		}
		else
		{
			battleQueue.push_back(enemyActiveCreep);
			battleQueue.push_back(playerActiveCreep);
		}

		int otherCreep = 1;
		/* Executes both of the players moves */
		for (int i = 0; i < battleQueue.size(); i++) 
		{
			category = battleQueue[i].nextMove.getCategory();
			level = battleQueue[i].getLevel();
			power = battleQueue[i].nextMove.power;

			if (category == "phys") //phys or spec
			{
				attack = battleQueue[i].getPhyAtkStat();
				defence = battleQueue[otherCreep].getPhyDefStat();
			}
			else
			{
				attack = battleQueue[i].getMagAtkStat();
				defence = battleQueue[otherCreep].getMagDefStat();
			}
			modifier = 1;

			if (i == 0) /* Only update the screen with the players damage info */
			{
				damage = ((((((2 * level) / 5) + 2)*power*(attack / defence) / 50) + 2)*modifier);
				displayDamage(playerOptions, damage, adamtesting);
				
				/* Gives the creep the damage to apply */
				trainer1.trainerCreeps[trainer1.activeCreepNum].attack(trainer2.trainerCreeps[trainer2.activeCreepNum], damage);

				otherCreep -= 1;
			}
			else
			{
				damage = ((((((2 * level) / 5) + 2)*power*(attack / defence) / 50) + 2)*modifier);
				displayDamage(playerOptions, damage, !adamtesting);

				/* Gives the creep the damage to apply */
				bool hasFainted = trainer2.trainerCreeps[trainer2.activeCreepNum].attack(trainer1.trainerCreeps[trainer1.activeCreepNum], damage);
				otherCreep += 1;

				if (hasFainted)
				{
					if (trainer1.faintedCreeps != 3)
					{
						int fainted = trainer1.activeCreepNum;
						changeCreep();
					}
					else
						endGame();
				}
			}
		}
		//waitEnterKey(playerOptions);
	} /* If the player has not chosen a move */
	else { 
		battleQueue.push_back(enemyActiveCreep);
		int otherCreep = 1;

			category = enemyActiveCreep.nextMove.getCategory();
			level = enemyActiveCreep.getLevel();
			power = enemyActiveCreep.nextMove.getPower();

			if (category == "phys") //phys or spec
			{
				attack = enemyActiveCreep.getPhyAtkStat();
				attack = enemyActiveCreep.getPhyAtkStat();
				defence = playerActiveCreep.getPhyDefStat();
			}
			else
			{
				attack = enemyActiveCreep.getMagAtkStat();
				defence = playerActiveCreep.getMagDefStat();
			}
			modifier = 1;
			damage = ((((((2 * level) / 5) + 2)*power*(attack / defence) / 50) + 2)*modifier);
			//vector<float> damageValues = { level, power, attack, defence };
			//damageDiagnostics(statusWindow, damageValues);
	}	
	enemyActiveCreep.bleed(statusWindow);
	playerActiveCreep.bleed(statusWindow);
	refresh();


	drawStatusBar(trainer1, playerStatusBar);
	drawStatusBar(trainer2, enemyStatusBar);

	/* Check if we should end the game */
	if (trainer1.checkWhiteOut() == true)
	{
		return true;
	}
	return false;
}

/* Prints 'Next', waits for the user to press enter */
int BattleManager::waitEnterKey(WINDOW* win)
{
	wclear(win);
	box(win, 0, 0);
	wattron(win, A_REVERSE);
	mvwaddstr(win, 3, 20, "Next");
	wattroff(win, A_REVERSE);
	wrefresh(win);

	while (int ch = getch() != 10){}

	wclear(win);
	box(win, 0, 0);
	wrefresh(win);
	return 1;
}

/* Displays a message to the user, displaying the damage they dealt */
int BattleManager::displayDamage(WINDOW* win, int damage, bool player)
{
	std::string text;
	if (player)	
		text = "You've inflicted " + to_string(damage) + " damage!";
	else 
		text = "The enemy dealt you " + to_string(damage) + " damage!";


	wclear(win);
	box(win, 0, 0);

	mvwaddstr(win, 2, 8, text.c_str());
	wattron(win, A_REVERSE);
	mvwaddstr(win, 4, 20, "Next");
	wattroff(win, A_REVERSE);
	wrefresh(win);

	while (int ch = getch() != 10) {}

	wclear(win);
	box(win, 0, 0);
	wrefresh(win);
	return 1;
}

/* Displays the components that calculate damage */
void BattleManager::damageDiagnostics(WINDOW* win, vector<float> values)
{	

	vector<std::string> headings = { "Level: ", "Power: ", "Attack: ", "Defence: " };
	box(win, 0, 0);
	for (int i = 0; i < values.size(); i++)
	{
		mvwaddstr(win, 1 + i, 12, headings[i].c_str());
		mvwaddstr(win, 1 + i, 1, to_string(values[i]).c_str());
	}
	mvwaddstr(win, 1, 15, trainer1.trainerCreeps[trainer1.activeCreepNum].getNextMove().c_str());
	wrefresh(win);
}

/* Displays the calculated damage in the window */ // OLD
void BattleManager::updateDamageInformation(WINDOW* win, float damage)
{
	wclear(win);
	box(win, 0, 0);

	std::string text = "You've inflicted " + to_string(damage) + " damage!";
	mvwaddstr(win, 5, 1, text.c_str());


	wrefresh(win);
}

/* Naviages the 4 main options the player can choose from (Fight, Creeps, Bag and Run (A.G) */
int BattleManager::playerChoice(int highlight)
{
	drawPlayerOptions(playerOptions, highlight);

	while (1)
	{
		int g = getch();
		switch (g)
		{
		case KEY_DOWN:
			switch (highlight)
			{
			case 0: highlight = 2; break;
			case 1: highlight = 3; break;
			} break;
		case KEY_UP:
			switch (highlight)
			{
			case 2: highlight = 0; break;
			case 3: highlight = 1; break;
			} break;
		case KEY_LEFT:
			switch (highlight)
			{
			case 1: highlight = 0; break;
			case 3: highlight = 2; break;
			} break;
		case KEY_RIGHT:
			switch (highlight)
			{
			case 0: highlight = 1; break;
			case 2: highlight = 3; break;
			} break;
		case 10:
			return highlight;
			break;
		}
		drawPlayerOptions(playerOptions, highlight);
	}
}

/* Visuals for the function playerChoice(). Draws the main options to the screen (A.G) */
void BattleManager::drawPlayerOptions(WINDOW* win, int highlight)
{
	const char* options[] = { "Fight",
							 "Creeps",
							 "Bag",
							 "Run"
	};

	for (int i = 0; i < 3; i++)
	{
		if (highlight == 0)
		{
			wattron(win, A_REVERSE);
			mvwaddstr(win, 2, 5, options[0]);
			wattroff(win, A_REVERSE);
			mvwaddstr(win, 2, 35, options[1]);
			mvwaddstr(win, 4, 5, options[2]);
			mvwaddstr(win, 4, 35, options[3]);
		}
		else if (highlight == 1)
		{
			mvwaddstr(win, 2, 5, options[0]);
			wattron(win, A_REVERSE);
			mvwaddstr(win, 2, 35, options[1]);
			wattroff(win, A_REVERSE);
			mvwaddstr(win, 4, 5, options[2]);
			mvwaddstr(win, 4, 35, options[3]);
		}
		else if (highlight == 2)
		{
			mvwaddstr(win, 2, 5, options[0]);
			mvwaddstr(win, 2, 35, options[1]);
			wattron(win, A_REVERSE);
			mvwaddstr(win, 4, 5, options[2]);
			wattroff(win, A_REVERSE);
			mvwaddstr(win, 4, 35, options[3]);
		}
		else if (highlight == 3)
		{
			mvwaddstr(win, 2, 5, options[0]);
			mvwaddstr(win, 2, 35, options[1]);
			mvwaddstr(win, 4, 5, options[2]);
			wattron(win, A_REVERSE);
			mvwaddstr(win, 4, 35, options[3]);
			wattroff(win, A_REVERSE);
		}
	}
	wrefresh(win);
}

/* Draws the Creeps moves to the screen and returns 0 - 3 of the move selected (A.G) */
int BattleManager::fightOptions(WINDOW* win)
{
	highlight = 0;
	drawFightOptions(win, highlight);

	int availableMoves = trainer1.trainerCreeps[trainer1.activeCreepNum].creepMoves.size();

	while (1)
	{
		/* Handles when the player only has 2/3/4 moves to choose from (Not visuals) */
		switch (availableMoves)
		{
			case 4:
			{
				int g = getch();
				switch (g)
				{
				case KEY_DOWN:
					switch (highlight)
					{
					case 0: highlight = 2; break;
					case 1: highlight = 3; break;
					} break;
				case KEY_UP:
					switch (highlight)
					{
					case 2: highlight = 0; break;
					case 3: highlight = 1; break;
					} break;
				case KEY_LEFT:
					switch (highlight)
					{
					case 1: highlight = 0; break;
					case 3: highlight = 2; break;
					} break;
				case KEY_RIGHT:
					switch (highlight)
					{
					case 0: highlight = 1; break;
					case 2: highlight = 3; break;
					} break;
				case 10:
					wclear(win);
					box(win, 0, 0);
					wrefresh(win);
					return highlight;
					break;
				}
				drawFightOptions(win, highlight);
				break;
			}
			case 3:
			{
				int g = getch();
				switch (g)
				{
				case KEY_DOWN:
					switch (highlight)
					{
					case 0: highlight = 2; break;
					} break;
				case KEY_UP:
					switch (highlight)
					{
					case 2: highlight = 0; break;
					} break;
				case KEY_LEFT:
					switch (highlight)
					{
					case 1: highlight = 0; break;
					} break;
				case KEY_RIGHT:
					switch (highlight)
					{
					case 0: highlight = 1; break;
					} break;
				case 10:
					wclear(win);
					box(win, 0, 0);
					wrefresh(win);
					return highlight;
					break;
				}
				drawFightOptions(win, highlight);
				break;
			}
			case 2:
			{
				int g = getch();
				switch (g)
				{
				case KEY_LEFT:
					switch (highlight)
					{
					case 1: highlight = 0; break;
					} break;
				case KEY_RIGHT:
					switch (highlight)
					{
					case 0: highlight = 1; break;
					} break;
				case 10:
					wclear(win);
					box(win, 0, 0);
					wrefresh(win);
					return highlight;
					break;
				}
				drawFightOptions(win, highlight);
				break;
			}
		}
	}
}

/* Visuals for the function fightOptions(). This returns 0-3 which identifes the move selected by the user (A.G) */
int BattleManager::drawFightOptions(WINDOW* win, int highlight)
{
	wclear(win);
	wrefresh(win);
	box(win, 0, 0);
	int availableMoves = trainer1.trainerCreeps[trainer1.activeCreepNum].creepMoves.size();

	for (int i = 0; i < 3; i++)
	{
		if (trainer1.trainerCreeps[i].getActiveState() == true)
		{
			switch (availableMoves)
			{
				case 4:
				{
					switch (highlight)
					{
					case 0:
						wattron(win, A_REVERSE);
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						wattroff(win, A_REVERSE);
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						mvwaddstr(win, 4, 33, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						break;
					case 1:
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						wattron(win, A_REVERSE);
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						wattroff(win, A_REVERSE);
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						mvwaddstr(win, 4, 33, trainer1.trainerCreeps[i].creepMoves[3].moveName.c_str());
						break;
					case 2:
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						wattron(win, A_REVERSE);
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						wattroff(win, A_REVERSE);
						mvwaddstr(win, 4, 33, trainer1.trainerCreeps[i].creepMoves[3].moveName.c_str());
						break;
					case 3:
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						wattron(win, A_REVERSE);
						mvwaddstr(win, 4, 33, trainer1.trainerCreeps[i].creepMoves[3].moveName.c_str());
						wattroff(win, A_REVERSE);
						break;
					case 10:
						return highlight;
						break;
					}
				}
				case 3:
				{
					switch (highlight)
					{
					case 0:
						wattron(win, A_REVERSE);
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						wattroff(win, A_REVERSE);
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						break;
					case 1:
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						wattron(win, A_REVERSE);
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						wattroff(win, A_REVERSE);
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						break;
					case 2:
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						wattron(win, A_REVERSE);
						mvwaddstr(win, 4, 4, trainer1.trainerCreeps[i].creepMoves[2].moveName.c_str());
						wattroff(win, A_REVERSE);
						break;
					case 10:
						return highlight;
						break;
					}
				}
				case 2:
				{
					switch (highlight)
					{
					case 0:
						wattron(win, A_REVERSE);
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						wattroff(win, A_REVERSE);
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						break;
					case 1:
						mvwaddstr(win, 2, 4, trainer1.trainerCreeps[i].creepMoves[0].moveName.c_str());
						wattron(win, A_REVERSE);
						mvwaddstr(win, 2, 33, trainer1.trainerCreeps[i].creepMoves[1].moveName.c_str());
						wattroff(win, A_REVERSE);
						break;
					case 10:
						return highlight;
						break;
					}
				}
			}
			
		}
	}
	wrefresh(win);
}

/* Draws a health bar inside a window, can display active creeps health (A.G) */
void BattleManager::drawStatusBar(Trainer &player, WINDOW* win)
{
	init_pair(1, COLOR_GREEN, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);


	float totalHealth = player.trainerCreeps[player.activeCreepNum].getHealthStat();
	float currentHealth = player.trainerCreeps[player.activeCreepNum].getHealth();

	float percentHealth = currentHealth / totalHealth;

	float counter = 0;

	for (int i = 1; i < 22; i++)
	{
		if (counter < percentHealth)
		{
			wattron(win, COLOR_PAIR(1));
			mvwaddch(win, 1, i * 2, 178);
			wattroff(win, COLOR_PAIR(1));
		}
		else
		{
			wattron(win, COLOR_PAIR(2));
			mvwaddch(win, 1, i * 2, 178);
			wattroff(win, COLOR_PAIR(2));
		}
		counter += 0.05;
	}

	//mvwaddstr(win, 0, 0, to_string(totalHealth).c_str());
	//mvwaddstr(win, 1, 0, to_string(currentHealth).c_str());
	//mvwaddstr(win, 0, 5, to_string(percentHealth).c_str());

	wattroff(win, COLOR_PAIR(1));
	wattroff(win, COLOR_PAIR(2));
	wrefresh(win);
}

/* Draws the active creep sprite inside a window (A.G) */
void BattleManager::drawCreep(Trainer &trainer, WINDOW* win)
{
	wclear(win);
	box(win, 0, 0);

	if (trainer.trainerCreeps[trainer.activeCreepNum].hasSprite)
	{
		for (int i = 0; i < trainer.trainerCreeps[trainer.activeCreepNum].creepVect.size(); i++)
		{
			mvwprintw(win, i + 1, 1, trainer.trainerCreeps[trainer.activeCreepNum].creepVect[i].c_str());
		}
	}	
	wrefresh(win);
}

/* Changes the current active creep and navigates the selection in the window (A.G) */
int BattleManager::changeCreep()
{
	drawChangeCreepWindow(changeCreeps, highlight);
	highlight = 0;
	while (1)
	{
		int g = getch();
		switch (g)
		{
		case KEY_DOWN:
			switch (highlight)
			{
			case 0: highlight = 1; break;
			case 1: highlight = 2; break;
			case 2: highlight = 0; break;
			} break;
		case KEY_UP:
			switch (highlight)
			{
			case 0: highlight = 2; break;
			case 1: highlight = 0; break;
			case 2: highlight = 1; break;
			} break;
		case KEY_BACKSPACE:// FIND OUT THE KEY FOR BACKSPACE
			return highlight;
			break;
		case 10:
		{	/* The case if the Creep has not fainted and is not currently in play */
			if (trainer1.trainerCreeps[highlight].getActiveState() != true && trainer1.trainerCreeps[highlight].getFaintedStatus() == false)
			{
				/* Deactivates the currently active creep */
				for (int i = 0; i < 3; i++)  
				{
					if (trainer1.trainerCreeps[i].getActiveState() == true)
					{
						trainer1.trainerCreeps[i].setActiveState(false);
					}
				}

				wclear(changeCreeps);
				wrefresh(changeCreeps);
				wclear(creepInfo);
				wrefresh(creepInfo);

				/* Activates the new creep */
				trainer1.trainerCreeps[highlight].setActiveState(true);
				return highlight;
			} /* The case where the creep is already out */
			else if (trainer1.trainerCreeps[highlight].getActiveState())
			{
				mvwaddstr(changeCreeps, 1, 1, "Already Out");
			} /* The case where the creep is fainted and not already in play */
			else if (trainer1.trainerCreeps[highlight].getFaintedStatus() == true)
			{
				mvwaddstr(changeCreeps, 1, 1, "This Creep has fainted");
			}
			break;
		}
		}
		drawChangeCreepWindow(changeCreeps, highlight);
		wclear(changeCreeps);
		box(changeCreeps, 0, 0);
	}
}

/* Visuals for the function changeCreep(). Creates a window and displays the available creeps (A.G) */
void BattleManager::drawChangeCreepWindow(WINDOW* win, int highlight)
{
	box(win, 0, 0);
	string creep_1 = trainer1.trainerCreeps[0].creepName;
	string creep_2 = trainer1.trainerCreeps[1].creepName;
	string creep_3 = trainer1.trainerCreeps[2].creepName;

	for (int i = 0; i < 3; i++)
	{
		if (highlight == 0)
		{
			wattron(win, A_REVERSE);
			mvwaddstr(win, 2, 3, creep_1.c_str());
			wattroff(win, A_REVERSE);
			mvwaddstr(win, 4, 3, creep_2.c_str());
			mvwaddstr(win, 6, 3, creep_3.c_str());
		}
		else if (highlight == 1)
		{
			mvwaddstr(win, 2, 3, creep_1.c_str());
			wattron(win, A_REVERSE);
			mvwaddstr(win, 4, 3, creep_2.c_str());
			wattroff(win, A_REVERSE);
			mvwaddstr(win, 6, 3, creep_3.c_str());
		}
		else if (highlight == 2)
		{
			mvwaddstr(win, 2, 3, creep_1.c_str());
			mvwaddstr(win, 4, 3, creep_2.c_str());
			wattron(win, A_REVERSE);
			mvwaddstr(win, 6, 3, creep_3.c_str());
			wattroff(win, A_REVERSE);
		}
	}
	trainer1.trainerCreeps[highlight].displayCreepInfo(creepInfo);
	wrefresh(win);
}

/* I.T. Giving player experience and money depending on who won */
int BattleManager::endGame() 
{
	if (gameOver == true) { //Player lost
		trainer1.trainerCreeps[trainer1.activeCreepNum].ChangeExperience(3);
	}
	else {
		trainer1.trainerCreeps[trainer1.activeCreepNum].ChangeExperience(15);
		trainer1.AddScore(50);
	}
	return 7;
}