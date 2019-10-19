#include <curses.h>
#include <fstream>
#include <string>

const char *choices[] = {
			"Play Game",
			"About Game",
			"Exit",
};

int n_choices = sizeof(choices) / sizeof(char *);
void print_menu(int highlight);
void printTitle();

int mainMenu()
{
	printTitle();

	int highlight = 1;
	int choice = 0;
	int c;

	refresh();
	print_menu(highlight);
	while (1)
	{
		c = getch();
		switch (c)
		{
		case KEY_UP:
			if (highlight == 1)
				highlight = n_choices;
			else
				--highlight;
			break;
		case KEY_DOWN:
			if (highlight == n_choices)
				highlight = 1;
			else
				++highlight;
			break;
		case 10:
			choice = highlight;
			if (choice == 1)
			{ return 1;	} // Play Game
			else if (choice == 2)
			{ return 7;	} // About Game
			else if (choice == 3)
			{ return -1; } // Exit
		default:
			refresh();
			break;
		}
		print_menu(highlight);
		if (choice != 0)	// User did a choice come out of the infinite loop 
			break;
			
	}
	
	return 0;
}

void printTitle()
{
	/* http://www.cplusplus.com/doc/tutorial/files/ */
	std::fstream title("../4007CEM_F5/text_files/main_menu_title.txt", std::ios::in);
	std::string line;
	int i = 4;

	while (std::getline(title, line))
	{
		mvaddstr(i , 0, line.c_str());		
		i += 1;
	}
	refresh();
	title.close();
}

void print_menu(int highlight)
{
	int x, y;
	for (int i = 0; i < n_choices; ++i)
	{
		y = (LINES / 2);
		x = (COLS / 2) - (sizeof(choices[i]));

		if (highlight == i + 1) /* High light the present choice */
		{
			attron(A_REVERSE);
			mvprintw(y + (i * 2), x, "%s", choices[i]);
			attroff(A_REVERSE);
		}
		else
			mvprintw(y + (i * 2), x, "%s", choices[i]);
		++y;
	}
	refresh();
}

void loadGame()
{

}