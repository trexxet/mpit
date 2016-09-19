#include "global.h"
#include "filesystem.h"

typedef void (*cmdFunc_t)();

typedef struct {
	char name[32];
	cmdFunc_t func;
} cmd_t;

//Commands interface
#define DIR_CURR gfTable[playerData.dir]
extern playerData_t playerData;		// Player data
extern gfile_t gfTable[];		// Filetable
int exists(char *name, uint16_t *id);	// If %name% exists, returns 1 and id, otherwise returns 0
#include "commands/include_cmds.h"

cmd_t cmds[NUM_OF_CMDS];

void initShell()
{
	#include "commands/init_list.c"
}

int exists(char *name, uint16_t *id)	//if %name% exists, returns 1 and id, otherwise returns 0
{
	#define DIR_SEARCH gfTable[searchDirID]
	int16_t searchDirID = playerData.dir;
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

// COMMAND LINE FUNCTIONS

void parseCommand(char *input);
void redrawInput(uint16_t cy, uint16_t cx, uint16_t offset, char *cmd);
uint16_t autocomplete(char *cmd, char buff[][MAX_INPUT_LENGTH], uint8_t tabKeystroke); // Returns number of variants

void getCommand(int *stop)
{
	extern char username[];
	noecho();
	printw("%s@MPIT:%s$ ", username, DIR_CURR.name);

	uint16_t cy, cx, offset = 8 + strlen(username) + strlen(DIR_CURR.name);	//8 == strlen("@MPIT:$ ")
	int input = 0;				// input = getch()
	char cmd[MAX_INPUT_LENGTH] = {0};	// input string
	// Autocompletion variables
	uint8_t tabKeystroke = 0;		// if Tab pressed once or twice
	char autocompBuff[MAX_SIZE_OF_AUTOCOMPLETE_BUFFER][MAX_INPUT_LENGTH] = {0}; //buffer for autocompletion
	uint16_t variants = 0;

	curs_set(1);
	#define CURS_POS (cx - offset)
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
				memmove(cmd + CURS_POS, cmd + CURS_POS + 1, strlen(cmd) - CURS_POS);
				redrawInput(cy, cx, offset, cmd);
				break;
			case KEY_BACKSPACE:
				if (cx > offset)
				{
					mvdelch(cy, cx - 1);
					memmove(cmd + CURS_POS - 1, cmd + CURS_POS, strlen(cmd) - CURS_POS);
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
				if (!tabKeystroke)
				{
					variants = autocomplete(cmd, autocompBuff, tabKeystroke);
					if (variants == 1)
					{
						strcpy(cmd, autocompBuff[0]);
						redrawInput(cy, offset + strlen(cmd), offset, cmd);
					}
					else
						tabKeystroke = 1;
				}
				else
				{
					for (int i = 0; i < variants; i++)
						mvprintw(cy + i + 1, 0, "%s", autocompBuff[i]);
					mvprintw(cy + variants + 1, 0, "%s@MPIT:%s$ ", username, DIR_CURR.name);
					redrawInput(cy + variants + 1, offset + strlen(cmd), offset, cmd);
				}
				break;
			case '\n':
				tabKeystroke = 0;
				break;
			default:
				memmove(cmd + CURS_POS + 1, cmd + CURS_POS, strlen(cmd) - cx + offset);
				cmd[CURS_POS] = input;
				redrawInput(cy, cx, offset, cmd);
				move(cy, cx + 1);
				tabKeystroke = 0;
				break;
		}
	}
	#undef CURS_POS
	curs_set(0);
	getyx(stdscr, cy, cx);
	move(cy + 1, 0);
	if ((strcmp(cmd, "quit") == 0) || (strcmp(cmd, "exit") == 0))
	{
		*stop = 1;
		return;
	}
	if (cmd[0] != 0)
		parseCommand(cmd);
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

uint16_t autocomplete(char *cmd, char buff[][MAX_INPUT_LENGTH], uint8_t tabKeystroke) // Returns number of variants
{
	extern uint16_t numofCommands;
	extern cmd_t cmds[];
	uint16_t variants = 0;
	// Clear buffer
	for (int i = 0; i < MAX_SIZE_OF_AUTOCOMPLETE_BUFFER; i++)
		buff[i][0] = 0;
	// Search for commands
	for (int i = 0; i < NUM_OF_CMDS; i++)
		if (strstr(cmds[i].name, cmd) == cmds[i].name)
		{
			sprintf(buff[variants], "%s ", cmds[i].name);
			variants++;
		}
	// Search for files
	// WOULD BE LATER
	return variants;
}

void redrawInput(uint16_t cy, uint16_t cx, uint16_t offset, char *cmd)
{
	move(cy, offset);
	clrtoeol();
	mvprintw(cy, offset, "%s", cmd);
	move(cy, cx);
}
