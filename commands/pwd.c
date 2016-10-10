#include "../filesystem.h"
#define DIR_TEMP gfTable[gdStack.IDs[gdStack.top]]

void _pwd()
{
	gdirIDStack gdStack = {};
	gdStack.IDs[1] = DIR_CURR.id;
	gdStack.top = 1;
	while (DIR_TEMP.id != 0)
	{
		gdStack.IDs[gdStack.top + 1] = DIR_TEMP.parent;
		gdStack.top++;
	}
	char path[256] = {};
	while (gdStack.top > 0)
	{
		strcat(path, DIR_TEMP.name);
		gdStack.top--;
	}
	printw("%s\n", path);
}

#undef DIR_TEMP
