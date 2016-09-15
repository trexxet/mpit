#include "global.h"
#include "filesystem.h"

gfile_t gfTable[MAX_FILES];

void initFilesystem()
{
	char fstructName[MAX_NAME_LEN] = {0};
	sprintf(fstructName, "%s%s%s", DATA_DIR, FILESYS_DIR, "filesystem.struct");
	FILE *fstruct = fopen(fstructName, "r");
	if (fstruct)
	{
		char buffer[256];
	
		#define FILE_CURR gfTable[newFileID]
		#define DIR_PARENT gfTable[gdStack.IDs[gdStack.top - 1]]
		gdirIDStack gdStack;
		gdStack.top = 0;
		uint16_t newFileID = 0;
		char fname[MAX_NAME_LEN];
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
				FILE_CURR.name[strlen(FILE_CURR.name) - 1] = 0;	//cut \n
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
				sprintf(fname, "%s%s%s", DATA_DIR, FILESYS_DIR, FILE_CURR.name);
				if (fcontent = fopen(fname, "r"))
				{
					fread(FILE_CURR.content, 1, MAX_FILE_LEN, fcontent);
					fclose(fcontent);
				}
				else
				{
					printw("External error in initFilesystem(): \n%s %s\n", 
							strerror(errno), FILE_CURR.name);
					break;
				}
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
	else
		printw("External error in initFilesystem():\n%s filesystem.struct\n", strerror(errno));
}
