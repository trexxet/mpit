#include "global.h"

playerData_t playerData;
char username[256];
char savefileName[256];

extern void boot();
extern void login();
extern void initFilesystem();
extern void initShell();
extern void getCommand(int *stop);

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
	boot();
	login();
	initFilesystem();
	initShell();
	int stop = 0;
	while (!stop)
		getCommand(&stop);
}
