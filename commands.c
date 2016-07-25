#include <string.h>
#include "global.h"
#include "filesystem.h"

typedef void (*cmdFunc_t)();

typedef struct {
	char name[32];
	cmdFunc_t func;
} cmd;

//Commands interface
#define DIR_CURR gdirTable[0 - playerData.dir]
extern playerData_t playerData;
extern gdir gdirTable[MAX_DIRS];
extern gfile gfileTable[MAX_FILES];
#include "commands/include_cmds.h"

cmd cmds[NUM_OF_CMDS];

void initCommands()
{
	#include "commands/init_list.c"
}

void parseCommand(char *input)
{
	uint8_t cmdFound;
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
