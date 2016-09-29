#include <wchar.h>
#include "global.h"

void boot()
{
	const static char *onloadMsg[] = {
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

void createNewUser()
{
	extern playerData_t playerData;
	playerData.dir = 0;
	playerData.stage = 0;
}

void login()
{
	extern char username[];
	_BOLD(printw("Welcome to the MPIT Systems!\n"));
	printw("Please sign in.\nLogin: ");
	_CURS_ON();
	scanw("%s", username);
	_CURS_OFF();
	_sleep(500);
	printw("\nLogged in as %s\n", username);


	char strtime[32];
	extern char saveFileName[];
	sprintf(saveFileName, "%s%s%s%s", DATA_DIR, SAVES_DIR, username, ".save");
	extern char histFileName[];
	sprintf(histFileName, "%s%s%s%s", DATA_DIR, SAVES_DIR, username, ".hist");
	extern playerData_t playerData;
	extern void loadSavedData();
	extern void loadHistory();
	FILE *saveFile = fopen(saveFileName, "rb");
	if (!saveFile)
	{
		printw("Last login: NULL\n\n");
		createNewUser();
	}
	else
	{
		loadSavedData();
		loadHistory();
		strftime(strtime, 32, "%Y-%m-%d %H:%M:%S", localtime(&(playerData.lastLoggedTime)));
		printw("Last login: %s\n\n", strtime);
	}
	refresh();
	time_t timer;
	time(&timer);
	playerData.lastLoggedTime = timer;
	extern void saveData();
	saveData();
	_sleep(500);
}
