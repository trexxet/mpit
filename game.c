#include "global.h"

playerData_t playerData;
char username[256];
char savefileName[256];

void loadSavedData()
{
	FILE *file = fopen(savefileName, "rb");
	if (file)
	{
		fread(&playerData, sizeof(playerData_t), 1, file);
		fclose(file);
	}
	else
		printw("External error in loadSavedData():\n%s\n", strerror(errno));
	file = NULL;
}

void saveData()
{
	FILE *file = fopen(savefileName, "wb");
	if (file)
	{
		fwrite(&playerData, sizeof(playerData_t), 1, file);
		fclose(file);
	}
	else
		printw("External error in saveData():\n%s\n", strerror(errno));
	file = NULL;
}

void gameStart()
{
	extern void boot();
	boot();
	extern void login();
	login();
	extern void initFilesystem();
	initFilesystem();
	extern void initShell();
	initShell();
	extern uint8_t stop;
	stop = 0;
	extern void getCommand();
	while (!stop)
		getCommand();
}
