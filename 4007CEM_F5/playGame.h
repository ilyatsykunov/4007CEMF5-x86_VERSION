#include <curses.h>
#include <string>

// ----- Play Game screen -----

const char *playGameChoices[] = {
			"Start Game",
			"Set Difficulty",
			"Back",
};

int n_playChoices = sizeof(playGameChoices) / sizeof(char *);
void print_playGame_menu(int highlight);

int playGame()
{
	int highlight = 1;
	int choice = 0;
	int c;

	refresh();
	print_playGame_menu(highlight);
	while (1)
	{
		c = getch();
		switch (c)
		{
			case KEY_UP:
				if (highlight == 1)
					highlight = n_playChoices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if (highlight == n_playChoices)
					highlight = 1;
				else
					++highlight;
				break;
			case 10:
				choice = highlight;
				if (choice == 1)
				{ return 7; } // Start game
				else if (choice == 2)
				{ return 8; } // Set Difficulty 
				else if (choice == 3)
				{ return 0; } // Back to Main Menu
			default:
				refresh();
				break;
		}
		print_playGame_menu(highlight);
		if (choice != 0) // User did a choice - come out of the infinite loop 
		break;
	}
}

void print_playGame_menu(int highlight)
{
	int x, y;
	for (int i = 0; i < n_playChoices; ++i)
	{
		y = (LINES / 2);
		x = (COLS / 2) - (sizeof(playGameChoices[i]));

		if (highlight == i + 1) /* Highlight the present choice */
		{
			attron(A_REVERSE);
			mvprintw(y + (i * 2), x, "%s", playGameChoices[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(y + (i * 2), x, "%s", playGameChoices[i]);
		++y;
	}
	refresh();
}

// ----- Set Difficulty screen -----

const char *difficultyRange[] = {
		"Easy",
		"Medium",
		"Hard",
		"Back"
};

int n_difChoices = sizeof(difficultyRange) / sizeof(char *);
void printDifMenu(int highlight);

int setDif()
{
	int highlight = 1;
	int choice = 0;
	int c;

	int y = (LINES / 2) - 1;
	int x = (COLS / 3);
	extern int difficulty;

	if (difficulty == 1)
	{
		char chosenDif[] = "Easy";
		mvprintw(y, x, "Current difficulty set: %s", chosenDif);
		refresh();
	}
	else if (difficulty == 2)
	{
		char chosenDif[] = "Medium";
		mvprintw(y, x, "Current difficulty set: %s", chosenDif);
		refresh();
	}
	else if (difficulty == 3)
	{
		char chosenDif[] = "Hard";
		mvprintw(y, x, "Current difficulty set: %s", chosenDif);
		refresh();
	}
	
	while (1)
	{
		c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_difChoices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_difChoices)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			if (choice == 1)
			{
				difficulty = 1;
			} // Easy difficulty
			else if (choice == 2)
			{
				difficulty = 2;
			} // Medium difficulty
			else if (choice == 3)
			{
				difficulty = 3;
			} // Hard difficulty
			else if (choice == 4)
			{
				return 1;
			} // Back to 'Play Game'

		default:
			return 1; // Back to 'Play Game'
			refresh();
			break;
		}
		printDifMenu(highlight);
		if (choice != 0) // User did a choice - come out of the infinite loop 
			break;
	}
	return 0;
};
void printDifMenu(int highlight)
{
	int x, y;
	for (int i = 0; i < n_difChoices; ++i)
	{
		y = (LINES / 2);
		x = (COLS / 2) - (sizeof(difficultyRange[i]));
		if (highlight == i + 1) // Highlight the present choice
		{
			attron(A_REVERSE);
			mvprintw(y + (i * 2), x, "%s", difficultyRange[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(y + (i * 2), x, "%s", difficultyRange[i]);
		++y;
	}
	refresh();
}