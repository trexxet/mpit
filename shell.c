#include "global.h"
#include "filesystem.h"
#include "shell.h"

uint16_t numofCommands;

//Commands interface
#define DIR_CURR gfTable[playerData.dir]
extern playerData_t playerData;
extern gfile_t gfTable[];
int exists(char *name, uint16_t *id);	/* If  %name% exists, returns 1 and id, otherwise returns 0. */
#include "commands/include_cmds.h"

cmd_t cmds[NUM_OF_CMDS];

void initShell()
{
	#include "commands/init_list.c"
	numofCommands = NUM_OF_CMDS;
}

void parseCommand(char *input)
{
	uint8_t cmdFound = 0;
	char *cmd = strtok(input, " ");
	for (int i = 0; i < NUM_OF_CMDS; i++)
		if (strcmp(cmd, cmds[i].name) == 0)
		{
			(*(cmds[i].func))();
			cmdFound = 1;
			break;
		}
	if (cmdFound == 0)
		printw("Command unknown or forbidden.\n");
}

int exists(char *name, uint16_t *id)	//if %name% exists, returns 1 and id, otherwise returns 0
{
	#define DIR_SEARCH gfTable[searchDirID]
	int16_t searchDirID = playerData.dir;
	/* Initially I wrote this:
	 * 	char *searchedName = strtok(name, "/");
	 * However, I discovered that searchedName has the same addres as name. Yes, it's rather obvious.
	 * But not for me. So strcat(searchedName, "/") made some shit with name. I love strings in C.*/
	char searchedName[MAX_FILE_LEN] = {0}, *tokPointer = NULL, *saveptr;
	int foundFlag;
	while (tokPointer = strtok_r(!tokPointer ? name : NULL, "/", &saveptr))
	{
		strcpy(searchedName, tokPointer);
		foundFlag = 0;
		if (strcmp(searchedName, "..") == 0)
		{
			foundFlag = 1;
			searchDirID = DIR_SEARCH.parent;
		}
		else
		{
			for (int i = 0; i < DIR_SEARCH.childnum; i++)	// scan for files
				if (strcmp(searchedName, gfTable[DIR_SEARCH.childs[i]].name) == 0)
				{
					foundFlag = 1;
					*id = DIR_SEARCH.childs[i];
					break;
				}
			strcat(searchedName, "/");
			for (int i = 0; i < DIR_SEARCH.childnum; i++)	//scan for directories
				if (strcmp(searchedName, gfTable[DIR_SEARCH.childs[i]].name) == 0)
				{
					foundFlag = 1;
					searchDirID = DIR_SEARCH.childs[i];
					*id = DIR_SEARCH.id;
					break;
				}
		}
	}
	return foundFlag;
	#undef DIR_SEARCH
}