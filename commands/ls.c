void _ls()
{
	for (int i = 0; i < DIR_CURR.childnum; i++)
	{
		uint16_t id = DIR_CURR.childs[i];
		if (gfTable[id].isdir)
			_BOLD(printw("%s\t", gfTable[id].name))
		else
			printw("%s\t", gfTable[id].name);
	}
	printw("\n");
	refresh();
}
