#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include "filesystem.h"

gfile gfTable[MAX_FILES];

void initFilesystem()
{
	FILE *fstruct = fopen("filesystem/filesystem.struct", "r");
	char buffer[256];

	#define FILE_CURR gfTable[newFileID]
	#define DIR_PARENT gfTable[gdStack.IDs[gdStack.top - 1]]
	gdirIDStack gdStack;
	gdStack.top = 0;
	uint16_t newFileID = 0;
	char fname[32 + 11]; // + "filename/"
	FILE *fcontent;
	while (fgets(buffer, 256, fstruct))
	{
		if (buffer[gdStack.top] == '\t') 	//enters new dir
			gdStack.top++;
		if (buffer[gdStack.top] == '\\') 	//exits dir
			gdStack.top--;
		if (buffer[gdStack.top] == '/')		//new dir
		{
			FILE_CURR.id = newFileID;
			FILE_CURR.isdir = 1;
			strcpy(FILE_CURR.name, buffer + gdStack.top + 1); // + '\t' + '/'
			FILE_CURR.name[strlen(FILE_CURR.name) - 1] = 0; //cut \n
			FILE_CURR.childnum = 0;
			if (gdStack.top > 0)
			{
				FILE_CURR.parent = DIR_PARENT.id;
				DIR_PARENT.childs[DIR_PARENT.childnum] = newFileID;
				DIR_PARENT.childnum++;
			}
			gdStack.IDs[gdStack.top] = newFileID;
			newFileID++;
		}
		else 
		if (buffer[gdStack.top + 1] != '\\')	//new file
		{
			FILE_CURR.id = newFileID;
			FILE_CURR.isdir = 0;
			strcpy(FILE_CURR.name, buffer + gdStack.top); // + '\t'
			FILE_CURR.name[strlen(FILE_CURR.name) - 1] = 0; //cut \n
			strcpy(fname, "filesystem/");
			fcontent = fopen(strcat(fname, FILE_CURR.name), "r");
			fread(FILE_CURR.content, 1, MAX_FILE_LEN, fcontent);
			fclose(fcontent);
			FILE_CURR.parent = DIR_PARENT.id;
			DIR_PARENT.childs[DIR_PARENT.childnum] = newFileID;
			DIR_PARENT.childnum++;
			newFileID++;
		}
	}
	#undef FILE_CURR
	#undef DIR_PARENT
	fclose(fstruct);
}
