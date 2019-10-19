/// Tournament.h this is the the tournament screen. It lets you go to battle screen and to shop screen
/// Made mainly using Kristaps' "Shop.h" code as an example and the NCURSES documentation - http://tldp.org/HOWTO/NCURSES-Programming-HOWTO/
/// Author - Ilya Tsykunov
#ifndef TOURNAMENT_H
#define TOURNAMENT_H

#include <curses.h>
#include <string>
#include <vector>
#include "trainer.h"
#include "Creep.h"
using namespace std;

Trainer trainer1;
Trainer trainer2;

const char *menuChoices[] = { //array of menu choices 
	"Start Fight!",
	"Shop",
	"Exit"
};
const char *menuList[] = { //blank array to be printed after the menu
	" "
};

int n_tournamentChoices = sizeof(menuChoices) / sizeof(char *); // ref - pdf
void print_tournamentMenu(int highlight, const char* shopChoices[]); //Function header for creating the interactive menu
WINDOW tournament_win(int, int, int, int, /*const char* [],*/ int); //Function header for creating windows 

int TournamentScreen()
{
	//Instantiating objects of Curses windows
	WINDOW score = tournament_win(3, 12, 24, 10, 0);
	WINDOW creepEnemy = tournament_win(13, 26, 1, 45, 1);
	WINDOW creep1 = tournament_win(8, 15, 21, 60, 2);
	WINDOW creep2 = tournament_win(8, 15, 21, 80, 3);
	WINDOW creep3 = tournament_win(8, 15, 21, 100, 4);

	/* Start of code taken from Kristaps' "Shop.h" code as an example*/
	int highlight = 1; // ref - pdf
	int choice = 0;
	int c;

	refresh();
	print_tournamentMenu(highlight, menuChoices);
	while (1)// ref - pdf
	{
		c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_tournamentChoices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_tournamentChoices)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			if (choice == 1)
			{
				return 3;
				break;
			}
			else if (choice == 2)
			{
				return 5;
				break;
			}
			else if (choice == 3)
			{
				return 0;
				break;
			}
		default:
			refresh();
			break;
		}
		print_tournamentMenu(highlight, menuChoices);
		if (choice != 0) // User did a choice - come out of the infinite loop 
			break;
	}
	/* End of code taken from Kristaps' "Shop.h" code as an example*/
}


WINDOW tournament_win(int height, int width, int starty, int startx, int listIndex) // Function body for instantiating windows. Made using the Curses library
{
	WINDOW* win = newwin(height, width, starty, startx); // creating instance of a window with parameters in brackets

	if (listIndex == 0)
	{
		string text = "Score: \n   " + to_string(trainer1.GetScore()); // declares variable storing player score
		mvwprintw(win, 1, 1, text.c_str()); // prints player score variable at y = 1, x = 1 coordinates
	}
	else if (listIndex == 1)
	{
		box(win, 0, 0); // drawing an outline for the window
		string text = "Next enemy is " + trainer2.trainerCreeps[trainer1.activeCreepNum].creepName;  // declaring variable storing enemy name
		mvwprintw(win, 1, 1, text.c_str()); // printing the string
		mvwprintw(win, 2, 1, "________________________"); // printing string of underscore characters to split the window into two at y = 2, x = 1 coordinates
	}
	else if (listIndex == 2)
	{
		box(win, 0, 0); // drawing an outline for the window
		string text = trainer1.trainerCreeps[0].creepName + " Lv. " + to_string(trainer1.trainerCreeps[0].getLevel()); // declaring variable storing creep 1 name and its level
		mvwprintw(win, 1, 1, text.c_str()); //printing the string
		mvwprintw(win, 2, 1, "_____________");  // printing string of underscore characters to split the window into two at y = 2, x = 1 coordinates
	}
	else if (listIndex == 3)
	{
		box(win, 0, 0); // drawing an outline for the window
		string text = trainer1.trainerCreeps[1].creepName + " Lv. " + to_string(trainer1.trainerCreeps[1].getLevel()); // declaring variable storing creep 2 name and its level
		mvwprintw(win, 1, 1, text.c_str()); // printing the string
		mvwprintw(win, 2, 1, "_____________");  // printing string of underscore characters to split the window into two at y = 2, x = 1 coordinates
	}
	else if (listIndex == 4)
	{
		box(win, 0, 0); // drawing an outline for the window
		string text = trainer1.trainerCreeps[2].creepName + " Lv. " + to_string(trainer1.trainerCreeps[2].getLevel()); // declaring variable storing creep 3 name and its level
		mvwprintw(win, 1, 1, text.c_str()); // printing the string
		mvwprintw(win, 2, 1, "_____________");  // printing string of underscore characters to split the window into two at y = 2, x = 1 coordinates
	}

	wrefresh(win); //Updating the window
	return *win; //Returning window object with updated values
}
void print_tournamentMenu(int highlight, const char *menuList[])// Made using Kristaps' "Shop.h" code as an example
{
	int n_menuList = sizeof(menuList);

	int x, y;
	for (int i = 0; i < n_menuList; ++i)
	{
		x = 15;
		y = (COLS / 2) - sizeof(menuList);

		if (highlight == i + 1) // Highlight the present choice
		{
			attron(A_REVERSE);
			mvprintw(x + (i * 2), y, "%s", menuList[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(x + (i * 2), y, "%s", menuList[i]);
		++x;
	}
	refresh();
}

#endif