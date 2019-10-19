#ifndef PREGAME_H
#define PREGAME_H
#include <curses.h>
#include <iostream>
#include <fstream>
#include <vector>

WINDOW *drawBracketBox(int, int, int, int, char[]);
WINDOW *textBox(int, int, int, int);
void printScroll(WINDOW* win, WINDOW* textBox, int highlight, const char* firstText[]);

int bracket(const char *trainers[])
{
	refresh();
	// intitialization

	char aHeader[] = "Group A Information";
	char bHeader[] = "Group B Information";

	const char *text[] = {  "All contestants are initially sorted into 2 groups that play 6 games each, depending",
							"on your performance will be placed into either the lower or the higher bracket in the",
							"playoffs."
	};
	WINDOW *bTwo = drawBracketBox(16, 30, 1, 10, aHeader);
	WINDOW *bOne = drawBracketBox(16, 30, 1, 60, bHeader);
	WINDOW *textOne = textBox(6, 90, 18, 3);
	WINDOW *textScroll = newwin(1, 20, LINES - 2 , COLS / 2 - 4);

	int choice = 1;
	int highlight = 0;
	// End of intitialization 

	for (int p = 0; p < 4; p++)
	{
		mvwprintw(bOne, 4 + (p * 3), 15, trainers[p]); // Prints the first groups trainers 
	}	 
	for (int i = 4; i < 8; i++)
	{
		mvwprintw(bTwo, 4 + ((i - 4) * 3), 15, trainers[i]); // Prints the second
	}
	for (int i = 0; i < 2; i++)
	{
		mvwaddstr(textOne, i, 0, text[i]);
	}

	wrefresh(textOne);
	wrefresh(bOne);
	wrefresh(bTwo);
	refresh();
	printScroll(textScroll, textOne, highlight, text);
	mvwaddstr(textScroll, 0, 6, "Next"); // Prints the scroll indicators
	wrefresh(textScroll);

	while (1) // Redraws the menu to highlight the current option
	{
		int c = getch();
		switch (c)
		{
		case KEY_RIGHT:
			if (highlight == 3)
				highlight = 0;
			else
				++highlight;
			break;
		case KEY_LEFT:
			if (highlight == 0)
				highlight = 3;
			else
				--highlight;
			break;
		case 10:
			if (highlight == 3)
			{
				return 3; // Return the page to go to when the user selects next
			}
		}
		printScroll(textScroll, textOne, highlight, text);
		wrefresh(textOne);
		wrefresh(textScroll);
	}
	//return 0;
}

WINDOW *drawBracketBox(int height, int width, int starty, int startx, char header[])
{
	WINDOW *win;
	win = newwin(height, width, starty, startx);

	int score[] = { 10 };

	box(win, 0, 0);
	mvwprintw(win, 1, 1, "%s", header);
	mvwprintw(win, 2, 1, "____________________________");

	for (int i = 3; i < height - 1; i++)
	{
		mvwprintw(win, i, 6, "|");
	}
	for (int j = 0; j < 4; j++)
	{
		mvwprintw(win, 4 + (j * 3), 2, "%i-%i", 0, 5);
	}

	return win;
}

WINDOW *textBox(int height, int width, int starty, int startx)
{
	WINDOW *win;
	win = newwin(height, width, starty, startx);
	wclear(win);
	return win;
}

void printScroll(WINDOW* win, WINDOW* textWin, int highlight, const char* firstText[])
{
	wclear(textWin); // Clears the window so new text can be displayed

	std::ifstream file;
	file.open("./text_files/pregame_bracket_text.txt", std::ios::in);
	std::string line;
	std::vector<std::string> fileText;

	while (file)
	{
		std::getline(file, line);
		fileText.push_back(line);
		line = "";
	}
	file.close();



	for (int i = 0; i < 4; i++)
	{
		if (highlight == i && i < 3)
		{
			wattron(win, A_REVERSE);
			mvwaddstr(win, 0, i * 2, ">");
			wattroff(win, A_REVERSE);
		}
		else if (i < 3)
		{
			mvwaddstr(win, 0, i * 2, ">");
			mvwaddstr(win, 0, 6, "Next");
		}
		else if (highlight == 3)
		{
			wattron(win, A_REVERSE);
			mvwaddstr(win, 0, i * 2, "Next");
			wattroff(win, A_REVERSE);
		}

		// End of main scroll functionality 

		
		int k;

		if (highlight == 0)
		{
			k = 0;
			for (int j = 5; j < 9; j++)
			{				
				mvwaddstr(textWin, k, 0, fileText[j].c_str());	
				k++;
			}
		}
		else if (highlight == 1)
		{
			k = 0;
			for (int j = 9; j < 12; j++)
			{
				mvwaddstr(textWin, k, 0, fileText[j].c_str());
				k++;				
			}
		}
		else if (highlight == 2)
		{
			k = 0;
			for (int j = 12; j < 15; j++)
			{
				mvwaddstr(textWin, k, 0, fileText[j].c_str());
				k++;				
			}
		}
	}
	wrefresh(textWin);
}



#endif