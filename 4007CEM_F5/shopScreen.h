#pragma once
#ifndef SHOPSCREEN_H
#define SHOPSCREEN_H

#include <string>
#include <vector> 
#include <curses.h>


void displayShopWindow(WINDOW*, int);
bool getPlayerOption(WINDOW*, WINDOW*, vector<Item>, bool);
void displayPlayerWindow(WINDOW*, int);


vector<Item> shopScreen(vector<Item> inventory)
{
	WINDOW* shopWindow = newwin(16, 30, 1, 50);
	WINDOW* playerWindow = newwin(16, 30, 1, 20);

	box(shopWindow, 0, 0);
	box(playerWindow, 0, 0);
	mvwprintw(shopWindow, 1, 13, "Shop");
	mvwprintw(shopWindow, 2, 1, "____________________________");
	mvwprintw(playerWindow, 1, 10, "Player Bag");
	mvwprintw(playerWindow, 2, 1, "____________________________");

	for (int i = 0; i < 12; i++)
	{
		mvwaddch(shopWindow, 3 + i, 23, '|');
	}
	for (int i = 0; i < 12; i++)
	{
		mvwaddch(playerWindow, 3 + i, 23, '|');
	}

	displayShopWindow(shopWindow, 0);
	displayPlayerWindow(playerWindow, -1);

	wrefresh(shopWindow);
	wrefresh(playerWindow);

	bool test = true;
	while (1)
	{
		test = getPlayerOption(shopWindow, playerWindow, inventory, test);
	}
	return inventory;
}

bool getPlayerOption(WINDOW* win, WINDOW* win2, vector<Item> inventory, bool option)
{
	int highlight = 0;
	wrefresh(win);

	while (1)
	{
		if (option)
		{
			displayShopWindow(win, highlight);
			displayPlayerWindow(win2, -1);
		}
		else
		{
			displayPlayerWindow(win2, highlight);
			displayShopWindow(win, -1);
		}

		int c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight > 0)			
				highlight--;			
			break;
		case KEY_DOWN:		
			if (highlight < 3)
				highlight++;
			break;
		case 10:
			if (highlight == 3)
				return (!option);
			break;
		}
	}

}

void displayPlayerWindow(WINDOW* win, int highlight)
{

	const char* shopText[] = { "Health Potion",
							   "Revive",
							   "Stat X" };

	for (int i = 1; i < 5; i++)
	{
		if (highlight == -1)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			mvwprintw(win, 8, 3, shopText[1]);
			mvwprintw(win, 10, 3, shopText[2]); 
			mvwprintw(win, 14, 3, "Go to Inventory");
		}
		if (highlight == 0)
		{
			wattron(win, A_REVERSE);
			mvwprintw(win, 6, 3, shopText[0]);
			wattroff(win, A_REVERSE);
			mvwprintw(win, 8, 3, shopText[1]);
			mvwprintw(win, 10, 3, shopText[2]);
			mvwprintw(win, 14, 3, "Go to Inventory");
		}
		else if (highlight == 1)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			wattron(win, A_REVERSE);
			mvwprintw(win, 8, 3, shopText[1]);
			wattroff(win, A_REVERSE);
			mvwprintw(win, 10, 3, shopText[2]);
			mvwprintw(win, 14, 3, "Go to Inventory");

		}
		else if (highlight == 2)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			mvwprintw(win, 8, 3, shopText[1]);
			wattron(win, A_REVERSE);
			mvwprintw(win, 10, 3, shopText[2]);
			wattroff(win, A_REVERSE);
			mvwprintw(win, 14, 3, "Go to Inventory");
		}
		else if (highlight == 3)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			mvwprintw(win, 8, 3, shopText[1]);
			mvwprintw(win, 10, 3, shopText[2]);
			wattron(win, A_REVERSE);
			mvwprintw(win, 14, 3, "Go to Inventory");
			wattroff(win, A_REVERSE);
		}
	}
	wrefresh(win);
}

void displayShopWindow(WINDOW* win, int highlight)
{
	const char* shopText[] = { "Health Potion", 
							   "Revive",
							   "Stat X" };

	for (int i = 1; i < 4; i++)
	{
		if (highlight == -1)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			mvwprintw(win, 8, 3, shopText[1]);
			mvwprintw(win, 10, 3, shopText[2]);
			mvwprintw(win, 14, 3, "Go to Inventory");
		}
		if (highlight == 0)
		{
			wattron(win, A_REVERSE);
			mvwprintw(win, 6, 3, shopText[0]);
			wattroff(win, A_REVERSE);
			mvwprintw(win, 8, 3, shopText[1]);
			mvwprintw(win, 10, 3, shopText[2]);
			mvwprintw(win, 14, 3, "Go to Inventory");
		}
		else if (highlight == 1)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			wattron(win, A_REVERSE);
			mvwprintw(win, 8, 3, shopText[1]);
			wattroff(win, A_REVERSE);
			mvwprintw(win, 10, 3, shopText[2]);
			mvwprintw(win, 14, 3, "Go to Inventory");

		}
		else if (highlight == 2)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			mvwprintw(win, 8, 3, shopText[1]);
			wattron(win, A_REVERSE);
			mvwprintw(win, 10, 3, shopText[2]);
			wattroff(win, A_REVERSE);
			mvwprintw(win, 14, 3, "Go to Inventory");
		}
		else if (highlight == 3)
		{
			mvwprintw(win, 6, 3, shopText[0]);
			mvwprintw(win, 8, 3, shopText[1]);
			mvwprintw(win, 10, 3, shopText[2]);
			wattron(win, A_REVERSE);
			mvwprintw(win, 14, 3, "Go to Inventory");
			wattroff(win, A_REVERSE);
		}
	}
	wrefresh(win);
}
/* 
health potion 
revive potion 
stat boosting
*/ 
#endif