#include <string.h>
#include <wchar.h>
#include "global.h"
#include "filesystem.h"

extern playerData_t playerData;
extern char username[];
extern gdir gdirTable[MAX_DIRS];
extern gfile gfileTable[MAX_FILES];
#define DIR_CURR gdirTable[0 - playerData.dir]

extern void parseCommand(char *input);

void boot()
{
	static char *onloadMsg[] = {
		"                             ",
		"Switching power on... ",
		"Initializating core... ",
		"Starting system... ",
		"Connetcting to server... "
	};
	#define LOGO_SIZEX 90
	#define LOGO_SIZEY 17
	extern uint16_t maxY, maxX;
	FILE *logo = fopen("bootlogo", "r");
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

int exists(char *name)
{
	
}

void terminal(int *stop)
{
	printw("%s@MPIT:%s$ ", username, DIR_CURR.name);
	char input[128];
	_CURS_ON();
	scanw("%s\n", input);
	_CURS_OFF();
	if ((strcmp(input, "quit") == 0) || (strcmp(input, "exit") == 0) || (input[0] == EOF))
	{
		*stop = 1;
		return;
	}
	parseCommand(input);
}
