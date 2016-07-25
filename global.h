#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <ncurses.h>
#include <stdint.h>
#include <unistd.h>
#include <time.h>

#define _sleep(tm) usleep(tm * 1000)
#define _BOLD(fnc)	attron(A_BOLD); \
			fnc; \
			attroff(A_BOLD);
#define _CURS_ON()	curs_set(1); \
			echo();
#define _CURS_OFF()	curs_set(0); \
			noecho();

typedef struct {
	time_t lastLoggedTime;
	int16_t dir;
	uint8_t stage;
} playerData_t;

#endif