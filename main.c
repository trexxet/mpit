#include <stdint.h>
#include <locale.h>
#include <ncurses.h>

#define STDSCR_FCOLOR COLOR_GREEN
#define STDSCR_BCOLOR COLOR_BLACK
#define STDSCR_COLORPAIR 1

uint16_t maxY, maxX;
extern void game_start(); //game.c

void init_ncurses()
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

void init_window()
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
	init_ncurses();
	init_window();

	game_start(maxY, maxX);

	finit();
	return 0;
}
