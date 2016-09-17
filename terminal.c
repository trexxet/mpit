#include <wchar.h>
#include "global.h"
#include "filesystem.h"
#include "shell.h"

extern playerData_t playerData;
extern char username[];
extern gfile_t gfTable[];
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
	extern uint16_t maxY, maxX;
	char flogo[128];
	sprintf(flogo, "%s%s", DATA_DIR, LOGO_FILE); 
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
	for (int i = 1; i <= 4; i++)
	{
		mvprintw(maxY - 1, 0, "%s", onloadMsg[i]);
		refresh();
		_sleep(250);
		mvprintw(maxY - 1, 0, "%s", onloadMsg[0]);
	}
	clear();
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
	for (int i = 0; i < numofCommands; i++)
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

void terminal(int *stop)
{
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
