#include <stdio.h>
#include <string.h>

#include "global.h"

extern void loadSavedData();
extern void saveData();

void createNewUser()
{
	extern playerData_t playerData;
	playerData.dir = 0;
	playerData.stage = 0;
}

void login()
{
	extern playerData_t playerData;
	extern char username[];
	extern char savefileName[];


	_BOLD(printw("Welcome to the MPIT Systems!\n"));
	printw("Please sign in.\nLogin: ");
	_CURS_ON();
	scanw("%s", username);
	_CURS_OFF();
	_sleep(500);
	printw("\nLogged in as %s\n", username);


	char strtime[32];
	strcpy(savefileName, username);
	strcat(savefileName, ".save");
	FILE *savefile = fopen(savefileName, "rb");
	if (!savefile)
	{
		printw("Last login: NULL\n\n");
		createNewUser();
	}
	else
	{
		loadSavedData();
		strftime(strtime, 32, "%Y-%m-%d %H:%M:%S", localtime(&(playerData.lastLoggedTime)));
		printw("Last login: %s\n\n", strtime);
	}
	refresh();
	time_t timer;
	time(&timer);
	playerData.lastLoggedTime = timer;
	saveData();
	_sleep(500);
}
