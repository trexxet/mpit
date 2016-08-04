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

int dirExists(char *name, int16_t *id)	//if directory %name% exists, returns 1 and id, otherwise returns 0
{
	#define DIR_SEARCH gdirTable[searchDirID]
	int16_t searchDirID = -playerData.dir;
	/* Initially I wrote this:
	 * 	char *searchedName = strtok(name, "/");
	 * However, I discovered that searchedName has the same addres as name. Yes, it's rather obvious.
	 * But not for me. So strcat(searchedName, "/") made some shit with name. */
	char searchedName[MAX_FILE_LEN] = {0}, lastName[MAX_NAME_LEN] = {0}, *tokPointer;
	int foundFlag;
	if (tokPointer = strtok(name, "/"))
		strcpy(searchedName, tokPointer);
	while (tokPointer)
	{
		strcat(searchedName, "/");
		foundFlag = 0;
		if (strcmp(searchedName, "../") == 0)
		{
			foundFlag = 1;
			searchDirID = -(DIR_SEARCH.parent);
			strcpy(lastName, DIR_SEARCH.name);
		}
		else
			for (int i = 0; i < DIR_SEARCH.childnum; i++)
				if (strcmp(searchedName, gdirTable[-(DIR_SEARCH.childs[i])].name) == 0)
				{
					foundFlag = 1;
					searchDirID = -(DIR_SEARCH.childs[i]);
					strcpy(lastName, searchedName);
					break;
				}
		if (tokPointer = strtok(NULL, "/"))
			strcpy(searchedName, tokPointer);
	}
	if ((strcmp(lastName, DIR_SEARCH.name) == 0) && foundFlag)
	{
		*id = DIR_SEARCH.id;
		return 1;
	}
	return 0;
	#undef DIR_SEARCH
}

void terminal(int *stop)
{
	printw("%s@MPIT:%s$ ", username, DIR_CURR.name);
	char input[128] = {0};
	_CURS_ON();
	getstr(input);
	_CURS_OFF();
	if ((strcmp(input, "quit") == 0) || (strcmp(input, "exit") == 0))
	{
		*stop = 1;
		return;
	}
	if (input[0] != 0)
		parseCommand(input);
}
