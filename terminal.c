#include <string.h>
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
		"Switching power on... ",
		"Initializating core... ",
		"Starting system... ",
		"Connetcting to server... "
	};
	for (int i = 0; i < 4; i++)
	{
		printw("%s", onloadMsg[i]);
		refresh();
		_sleep(500);
		_BOLD(printw("DONE\n"));
		refresh();
		_sleep(250);
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
