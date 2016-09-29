#pragma once

#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#include "config.h"

#define _sleep(tm) usleep(tm * 1000)
#define _BOLD(fnc)	{ attron(A_BOLD); \
			fnc; \
			attroff(A_BOLD); }
#define _CURS_ON()	{ curs_set(1); \
			echo(); }
#define _CURS_OFF()	{ curs_set(0); \
			noecho(); }

typedef struct {
	time_t lastLoggedTime;
	uint16_t dir;
	uint8_t stage;
} playerData_t;

typedef struct
{
	// Current position for writing in history list
	uint16_t wpos;
	// Current position for searching in history list
	uint16_t pos;
	// List
	char list[MAX_SIZE_OF_HISTORY_LIST][MAX_INPUT_LENGTH];
} historyData_t;
