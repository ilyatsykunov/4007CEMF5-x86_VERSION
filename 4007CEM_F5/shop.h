/// Header file for the shop screen, contains displaying store and player inventories and buy/selling features
/// 

#ifndef SHOP_H
#define SHOP_H

#include <curses.h>
using namespace std;


const char *shopMenu[] = { //creates array for options displayed for the player
	"Buy",
	"Sell",
	"Back"
};
int shopMenuSize = sizeof(shopMenu) / sizeof(char *); // ref - pdf
//        3       =          24         /      8w
void print_shopMenu(int highlight);

WINDOW shop_win(int, int, int, int, /*const char* [],*/ int); //identifies shop_win with parameter types

// ------ shopScreen, the main function to run when shop screen is opened ------

int shop()
{
	int width = COLS / 2 - 2;
	WINDOW shopInv = shop_win(15, width, 1, 1, 1);// itemList, 1); // creates an instance of shop_win under the name of shopInv with arguments given in brackets
	WINDOW playerInv = shop_win(15, width, 1, width + 1, 2);// invList, 2); // creates an instance of shop_win under the name of playerInv with arguments given in brackets

	int highlight = 1; // ref - pdf
	int choice = 0;
	int c;
	int shopBuy();
	int shopSell();

	print_shopMenu(highlight);
	while (1)// ref - pdf
	{
		c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = shopMenuSize;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == shopMenuSize)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			if (choice == 1)
			{
				return shopBuy();
				// Buy
				break;
			}
			else if (choice == 2)
			{
				return shopSell();
				// Sell
				break;
			}
			else if (choice == 3)
			{
				return 7; // Returns to main menu when 'back' selected - temporary for testing
				// Back
				break;
			}
		default:
			refresh();
			break;
		}
		print_shopMenu(highlight);
		if (choice != 0) // User did a choice - come out of the infinite loop 
			break;
	}
}

// ------ shopBuy function for buying in the shop ------

const char *itemList[] = { //creates an array of strings that contain item names - as simulated shop inventory
	"Health Potion",
	"Revive Potion",
	"Boost Potion",
};
int shopListSize = sizeof(itemList) / sizeof(char *);
void print_shopStock(int highlight);// const char* itemList[]);

int shopBuy()
{
	int highlight = 1;
	int choice = 0;
	int c;

	const char* labelText = "Q - Back    ENTER - Select";
	mvprintw(16, (COLS / 2) - (strlen(labelText) / 2), labelText);

	print_shopStock(highlight);
	while (1)
	{
		c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = shopListSize;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == shopListSize)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			if (choice == 1)
			{
				// DB code...
				// Health Potion chosen
				break;
			}
			else if (choice == 2)
			{
				// DB code...
				// Revive Potion chosen
				break;
			}
			else if (choice == 3)
			{
				// DB code...
				// Boost Potion chosen
				break;
			}
		case 113:
			return 7;
		default:
			refresh();
			break;
		}
		print_shopStock(highlight);
		if (choice != 0) // User did a choice - come out of the infinite loop 
			break;
	}
}

void print_shopStock(int highlight)
{
	int x, y;
	bool line;
	x = 2;
	y = 4;
	line = true;
	for (int i = 0; i < shopListSize; i++)
	{
		int whitespace = (COLS / 4) - (strlen(itemList[i]) + 3);

		if (y == 15)
		{
			y = 4;
			x = 30;
			line = false;
		}
		else
		{
			x = 2;
		}

		if (highlight == i + 1)
		{
			attron(A_REVERSE);
			mvprintw(y, x, itemList[i]);
			for (int i = 0; i < whitespace; i++)
			{
				addch(' ');
			}
			attroff(A_REVERSE);
		}
		else
		{
			mvprintw(y, x, itemList[i]);
			for (int i = 0; i < whitespace; i++)
			{
				addch(' ');
			}
		}
		y = y + 1;
		if (line == true)
			addch('|');
	}
	refresh();
}

// ------ shopSell function for selling in the shop ------

const char *invList[] = { //creates an array of strings that contain item names - as simulated player inventory
	"Health Potion"
};
int playerInvSize = sizeof(invList) / sizeof(char *);
void print_playerStock(int highlight);// const char* itemList[]);

int shopSell()
{
	int highlight = 1;// ref - pdf
	int choice = 0;
	int c;

	const char* labelText = "Q - Back    ENTER - Select";
	mvprintw(16, (COLS / 2) - (strlen(labelText) / 2), labelText);

	print_playerStock(highlight);
	while (1)
	{
		c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = playerInvSize;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == playerInvSize)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			if (choice == 1)
			{

				// Shop item 1
				break;
			}
			else if (choice == 2)
			{
				// Shop item 2 ...
				break;
			}
		case 113:
			return 7;
		default:
			refresh();
			break;
		}
		print_playerStock(highlight);
		if (choice != 0) // User did a choice - come out of the infinite loop 
			break;
	}
}

void print_playerStock(int highlight)
{
	int x, y;
	bool line;
	x = 60;
	y = 4;
	line = true;
	for (int i = 0; i < playerInvSize; i++)
	{
		//int itemAmount;
		//itemAmount = 2; // replace number with item DB reference of how many of [i] item player has
		//const char * itemAmountStr = " x", int itemAmount;

		int whitespace = (COLS / 4) - (strlen(itemList[i]) + 3/*+ strlen(itemAmountStr)*/);

		if (y == 15)
		{
			y = 4;
			x = 88;
			line = false;
		}
		else
		{
			x = 60;
		}

		if (highlight == i + 1)
		{
			attron(A_REVERSE);
			mvprintw(y, x, invList[i]);
			//mvprintw(y, x + strlen(itemList[i]), itemAmountStr);
			for (int i = 0; i < whitespace; i++)
			{
				addch(' ');
			}
			attroff(A_REVERSE);
		}
		else
		{
			mvprintw(y, x, invList[i]);
			//mvprintw(y, x + strlen(itemList[i]), itemAmountStr);
			for (int i = 0; i < whitespace; i++)
			{
				addch(' ');
			}
		}
		y++;
		if (line == true)
			addch('|');
	}
}

// ------ Function to print the shop menu as well as preview of shop and player stock ------

void print_shopMenu(int highlight)// ref - pdf
{
	int x, y;
	bool line;
	x = 2;
	y = 4;
	line = true;
	for (int i = 0; i < shopListSize; i++)
	{
		int whitespace = (COLS / 4) - (strlen(itemList[i]) + 3);
		if (y == 15)
		{
			y = 4;
			x = 30;
			line = false;
		}
		else
		{
			x = 2;
		}
		mvprintw(y, x, itemList[i]);
		for (int i = 0; i < whitespace; i++)
		{
			addch(' ');
		}
		y++;
		if (line == true)
			addch('|');
	}

	x = 60;
	y = 4;
	line = true;
	for (int i = 0; i < playerInvSize; i++)
	{
		int whitespace = (COLS / 4) - (strlen(invList[i]) + 3);
		if (y == 15)
		{
			y = 4;
			x = 88;
			line = false;
		}
		else
		{
			x = 60;
		}
		mvprintw(y, x, invList[i]);
		for (int i = 0; i < whitespace; i++)
		{
			addch(' ');
		}
		y++;
		if (line == true)
			addch('|');
	}

	for (int i = 0; i < shopMenuSize; ++i)
	{
		y = 20;
		x = (COLS / 2) - shopMenuSize;

		if (highlight == i + 1) // Highlight the present choice
		{
			attron(A_REVERSE);
			mvprintw(y + (i * 2), x, "%s", shopMenu[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(y + (i * 2), x, "%s", shopMenu[i]);
		++y;
	}
}

// ------ Window function that prints inventory borders and titles ------

WINDOW shop_win(int height, int width, int starty, int startx, /*const char* list[],*/ int listIndex) // shop_win function to create window and print window borders
{
	WINDOW *loc_win;
	loc_win = newwin(height, width, starty, startx); // creates new window 

	if (listIndex == 1)
	{
		box(loc_win, 0, 0); // draws ncurses box as a border for our inventory
		string title = "Shop"; // declares title variable
		mvwprintw(loc_win, 1, 1, title.c_str()); // prints title variable at y = 1, x = 1 coordinates
		wmove(loc_win, 2, 1); // moves cursor to y = 2, x = 1
		for (int i = 0; i < 56; i++) // prints a seperation line below box title
		{
			waddch(loc_win, '_');
		}

	}
	else if (listIndex == 2)
	{
		box(loc_win, 0, 0); // draws ncurses box as a border for our inventory
		string title = "Your Bag";
		mvwprintw(loc_win, 1, 1, title.c_str());
		wmove(loc_win, 2, 1);
		for (int i = 0; i < 56; i++)
		{
			waddch(loc_win, '_');
		}
	}
	wrefresh(loc_win);
	return *loc_win;
}

/*

#include <curses.h>
#include "Trainer.h"

class Shop
{ // Provides the interaction between the player and the shop database
private:

public:
	Shop()
	{
	};

	void getInventory()
	{
		// Query the database for the stock of the Shop
	}

	int getItemStock(int itemID) const
	{
		// Query the database for the stock of the itemID
	}

	void sellItem(Trainer& player, int itemID, int quantity)
	{
		// Calculate the total money generated from the sold items

		player.removeItem(itemID, quantity);
		// Update the item quantity

		player.increaseMoney(//total cost of items);

	}

	void buyItem(Trainer& player, int itemID, int quantity)
	{
		// Caluclate the total cost of the item(s)

		if (player.getMoney() >= //item(s) price)
		{
			player.addItem(itemID, quantity);
			// Update the item quantity
		}
	}


};
*/

#endif