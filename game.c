#include "global.h"

playerData_t playerData;
historyData_t histData;
char username[256];
char saveFileName[256];
char histFileName[256];

void loadSavedData()
{
	FILE* saveFile = fopen(saveFileName, "rb");
	if (saveFile)
	{
		fread(&playerData, sizeof(playerData_t), 1, saveFile);
		fclose(saveFile);
	}
	else
		printw("External error in loadSavedData():\n%s\n", strerror(errno));
	saveFile = NULL;
}

void saveData()
{
	FILE* saveFile = fopen(saveFileName, "wb");
	if (saveFile)
	{
		fwrite(&playerData, sizeof(playerData_t), 1, saveFile);
		fclose(saveFile);
	}
	else
		printw("External error in saveData():\n%s\n", strerror(errno));
	saveFile = NULL;
}

void loadHistory()
{
	FILE* histFile = fopen(histFileName, "rb");
	if (histFile)
	{
		fread(&histData, sizeof(historyData_t), 1, histFile);
		fclose(histFile);
	}
	else
		printw("External error in loadHistory():\n%s\n", strerror(errno));
	histFile = NULL;
}

void saveHistory()
{
	FILE* histFile = fopen(histFileName, "wb");
	if (histFile)
	{
		fwrite(&histData, sizeof(historyData_t), 1, histFile);
		fclose(histFile);
	}
	else
		printw("External error in saveHistory():\n%s\n", strerror(errno));
	histFile = NULL;
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
	saveHistory();
}
