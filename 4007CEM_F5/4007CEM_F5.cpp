
#include "mainMenu.h"
#include "playGame.h"
#include "preGameBracket.h"
#include "shop.h"
#include "Trainer.h"
#include "Creep.h"
#include "Item.h"
#include "ShopClass.h"
#include "battleScreen.h"
#include "Database.h"
#include "battleManager.h"
#include <curses.h>
#include "shopScreen.h"
#include "Tournament.h"

int difficulty = 2;

int main()
{

	const char *trainers[] = {
		"Gary",
		"Red",
		"Adam",
		"Dragos",
		"David",
		"Ilya",
		"Paul",
		"Kristaps"
	};
	

	initscr();
	clear();
	noecho();
	cbreak();	// Line buffering disabled. pass on everything 
	keypad(stdscr, TRUE);
	start_color();

	bool isRunning = true;

	int page = 0;
	vector<Item> trainerInventory = {};

	while (isRunning == true)
	{ 
		/*
		0 - Main Menu
		1 - Play Game
		2 - Pre Game Bracket Screen
		3 - Battle Screen (Gameplay screen)
		4 - Bracket Information
		5 - Shop
		6 - Leaderboards (End of Game)
		7 - About Game
		8 - Set Difficulty
		9 - Shop Test (Adam)
		*/

		switch (page)
		{
		case 0:
			page = mainMenu();
			break;
		case 1:
			page = playGame();
			break;
		case 2:
			trainerInventory = shopScreen(trainerInventory);
			page = 3;
			break;
		case 3:
		{
			BattleManager* battle = new BattleManager(trainerInventory);
			page = battle->GameLoop();
			delete battle;
			break;
		}
		case 4:
			//page = 
			break;
		case 5:
			page = shop();
			break;
		case 6:
			//page = 
			break;
		case 7:			
			page = TournamentScreen();
			break;
		case 8:
			page = setDif();
			break;
		case -1:
			isRunning = false;
			break;
		}
		clear();
		refresh();
	}
	endwin();
	return 0;
}
