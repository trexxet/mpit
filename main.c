#include <stdint.h>
#include <ncurses.h>

#define STDSCR_FCOLOR COLOR_GREEN
#define STDSCR_BCOLOR COLOR_BLACK
#define STDSCR_COLORPAIR 1

extern void game_start(uint16_t maxY, uint16_t maxX); //game.c

void init_ncurses(uint16_t *maxY, uint16_t *maxX)
{
	initscr();
	getmaxyx(stdscr, *maxY, *maxX);
	start_color();
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
	uint16_t maxY, maxX;
	init_ncurses(&maxY, &maxX);
	init_window();

	game_start(maxY, maxX);

	finit();
	return 0;
}
