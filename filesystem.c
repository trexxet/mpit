#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "filesystem.h"

gdir gdirTable[MAX_DIRS];
gfile gfileTable[MAX_FILES];

void initFilesystem()
{
	FILE *fstruct = fopen("filesystem/filesystem.struct", "r");
	char buffer[256];

	#define FILE_CURR gfileTable[newFileID - 1]
	#define DIR_CURR gdirTable[-newDirID]
	#define DIR_PARENT gdirTable[-gdStack.IDs[gdStack.top - 1]]
	gdirIDStack gdStack;
	gdStack.top = 0;
	uint16_t newFileID = 1;
	int16_t newDirID = 0;
	char fname[32 + 11]; // + "filename/"
	FILE *fcont;
	while (fgets(buffer, 256, fstruct))
	{
		if (buffer[gdStack.top] == '\t') 	//enters new dir
			gdStack.top++;
		if (buffer[gdStack.top] == '\\') 	//exits dir
			gdStack.top--;
		if (buffer[gdStack.top] == '/')		//new dir
		{
			DIR_CURR.id = newDirID;
			strcpy(DIR_CURR.name, buffer + gdStack.top + 1); // + '\t' + '/'
			DIR_CURR.name[strlen(DIR_CURR.name) - 1] = 0; //cut \n
			DIR_CURR.childnum = 0;
			if (gdStack.top > 0)
			{
				DIR_CURR.parent = DIR_PARENT.id;
				DIR_PARENT.childs[DIR_PARENT.childnum] = newDirID;
				DIR_PARENT.childnum++;
			}
			gdStack.IDs[gdStack.top] = newDirID;
			newDirID--;
		}
		else 
		if (buffer[gdStack.top + 1] != '\\')	//new file
		{
			FILE_CURR.id = newFileID;
			strcpy(FILE_CURR.name, buffer + gdStack.top); // + '\t'
			FILE_CURR.name[strlen(FILE_CURR.name) - 1] = 0; //cut \n
			strcpy(fname, "filesystem/");
			fcont = fopen(strcat(fname, FILE_CURR.name), "r");
			fread(FILE_CURR.cont, 1, MAX_FILE_LEN, fcont);
			fclose(fcont);
			FILE_CURR.parent = DIR_PARENT.id;
			DIR_PARENT.childs[DIR_PARENT.childnum] = newFileID;
			DIR_PARENT.childnum++;
			newFileID++;
		}
	}
	#undef FILE_CURR
	#undef DIR_CURR
	#undef DIR_PARENT
	fclose(fstruct);
}
