#include <stdio.h>

#include "global.h"

playerData_t playerData;
char username[256];
char savefileName[256];

extern void boot();
extern void login();
extern void initFilesystem();
extern void initCommands();
extern void terminal(int *stop);

void loadSavedData()
{
	FILE *file = fopen(savefileName, "rb");
	fread(&playerData, sizeof(playerData_t), 1, file);
	fclose(file);
	file = NULL;
}

void saveData()
{
	FILE *file = fopen(savefileName, "wb");
	fwrite(&playerData, sizeof(playerData_t), 1, file);
	fclose(file);
	file = NULL;
}

void game_start(uint16_t maxY, uint16_t maxX)
{
	//boot();
	login();
	initFilesystem();
	initCommands();
	int stop = 0;
	while (!stop)
		terminal(&stop);
}
