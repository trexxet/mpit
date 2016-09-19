#include <wchar.h>
#include "global.h"

extern void loadSavedData();
extern void saveData();

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
	sprintf(savefileName, "%s%s%s%s", DATA_DIR, SAVES_DIR, username, ".save");
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
