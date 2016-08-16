#include <wchar.h>
#include "global.h"
#include "filesystem.h"

extern playerData_t playerData;
extern char username[];
extern gfile gfTable[MAX_FILES];
#define DIR_CURR gfTable[playerData.dir]

extern void parseCommand(char *input);

void boot()
{
	static char *onloadMsg[] = {
		"                         ",
		"Switching power on... ",
		"Initializating core... ",
		"Starting system... ",
		"Connetcting to server... "
	};
	#define LOGO_SIZEX 90
	#define LOGO_SIZEY 17
	extern uint16_t maxY, maxX;
	char flogo[128];
	sprintf(flogo, "%s%s", getenv("HOME"), "/.mpit/bootlogo"); 
	FILE *logo = fopen(flogo, "r");
	wchar_t buffer[LOGO_SIZEX + 2];
	int i = 0;
	while (fgetws(buffer, LOGO_SIZEX + 2, logo) && (i < LOGO_SIZEY))
	{
		mvprintw((maxY - LOGO_SIZEY) / 2 + i, (maxX - LOGO_SIZEX) / 2,  "%ls\n", buffer);
		refresh();
		i++;
	}
	fclose(logo);
	#undef LOGO_SIZEX
	#undef LOGO_SIZEY
	for (int i = 1; i <= 4; i++)
	{
		mvprintw(maxY - 1, 0, "%s", onloadMsg[i]);
		refresh();
		_sleep(250);
		mvprintw(maxY - 1, 0, "%s", onloadMsg[0]);
	}
	clear();
}

void redrawInput(uint16_t cy, uint16_t cx, uint16_t offset, char *cmd)
{
	move(cy, offset);
	clrtoeol();
	mvprintw(cy, offset, "%s", cmd);
	move(cy, cx);
}

void terminal(int *stop)
{
	noecho();
	printw("%s@MPIT:%s$ ", username, DIR_CURR.name);
	uint16_t cy, cx, offset = 8 + strlen(username) + strlen(DIR_CURR.name);	//8 == strlen("@MPIT:$ ")
	int input = 0;
	char cmd[128] = {0};
	curs_set(1);
	while (input != '\n')
	{
		getyx(stdscr, cy, cx);
		switch (input = getch())
		{
			case KEY_LEFT:
				if (cx > offset)
					move(cy, cx - 1);
				break;
			case KEY_RIGHT:
				if (cx < (offset + strlen(cmd)))
					move(cy, cx + 1);
				break;
			case KEY_DC:
				delch();
				memmove(cmd + cx - offset, cmd + cx - offset + 1, strlen(cmd) - cx + offset);
				redrawInput(cy, cx, offset, cmd);
				break;
			case KEY_BACKSPACE:
				if (cx > offset)
				{
					mvdelch(cy, cx - 1);
					memmove(cmd + cx - offset - 1, cmd + cx - offset, strlen(cmd) - cx + offset);
					cmd[strlen(cmd) - 1] = 0;
					redrawInput(cy, cx, offset, cmd);
					move(cy, cx - 1);
				}
				break;
			case KEY_UP:
				break;
			case KEY_DOWN:
				break;
			case '\t':
				break;
			case '\n':
				break;
			default:
				memmove(cmd + cx - offset + 1, cmd + cx - offset, strlen(cmd) - cx + offset);
				cmd[cx - offset] = input;
				redrawInput(cy, cx, offset, cmd);
				move(cy, cx + 1);
				break;
		}
	}
	curs_set(0);
	addch('\n');
	if ((strcmp(cmd, "quit") == 0) || (strcmp(cmd, "exit") == 0))
	{
		*stop = 1;
		return;
	}
	if (cmd[0] != 0)
		parseCommand(cmd);
}
