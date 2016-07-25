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
	#define DIR_CURR gdirTable[0 - newDirID]
	#define DIR_PREV gdStack.IDs[gdStack.top - 1]
	gdirIDStack gdStack;
	gdStack.top = 0;
	uint16_t newFileID = 1;
	int16_t newDirID = 0;
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
			strcpy(DIR_CURR.name, strtok(buffer, "\t\n"));
			DIR_CURR.filenum = 0;
			if (gdStack.top > 0)
			{
				gdirTable[DIR_PREV].files[gdirTable[DIR_PREV].filenum] = newDirID;
				gdirTable[DIR_PREV].filenum++;
			}
			gdStack.IDs[gdStack.top] = newDirID;
			newDirID--;
		}
		else 
		if (buffer[gdStack.top + 1] != '\\')	//new file
		{
			FILE_CURR.id = newFileID;
			strcpy(FILE_CURR.name, strtok(buffer, "\t\n"));
			strcpy(FILE_CURR.fname, "filesystem/");
			strcat(FILE_CURR.fname, FILE_CURR.name); 
			fcont = fopen(FILE_CURR.fname, "r");
			fread(FILE_CURR.cont, 1, MAX_FILE_LEN, fcont);
			fclose(fcont);
			gdirTable[DIR_PREV].files[gdirTable[DIR_PREV].filenum] = newFileID;
			gdirTable[DIR_PREV].filenum++;
			newFileID++;
		}
	}
	#undef FILE_CURR
	#undef DIR_CURR
	#undef DIR_PREV
	fclose(fstruct);
}
