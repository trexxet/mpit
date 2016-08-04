#include <stdint.h>
#include <locale.h>
#include <ncurses.h>

#define STDSCR_FCOLOR COLOR_GREEN
#define STDSCR_BCOLOR COLOR_BLACK
#define STDSCR_COLORPAIR 1

uint16_t maxY, maxX;
extern void gameStart(); //game.c

void initNcurses()
{
	setlocale(LC_ALL, "");
	initscr();
	getmaxyx(stdscr, maxY, maxX);
	start_color();
	scrollok(stdscr, TRUE);
	cbreak();
	noecho();
	keypad(stdscr, true);
}

void initWindow()
{
	init_pair(STDSCR_COLORPAIR, STDSCR_FCOLOR, STDSCR_BCOLOR);
	wbkgd(stdscr, COLOR_PAIR(STDSCR_COLORPAIR));
	curs_set(0);
	refresh();
}

void finit()
{
	endwin();
}

int main()
{
	initNcurses();
	initWindow();

	gameStart(maxY, maxX);

	finit();
	return 0;
}
