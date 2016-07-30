void ls()
{
	for (int i = 0; i < DIR_CURR.filenum; i++)
	{
		int16_t id = DIR_CURR.files[i];
		if (id > 0)
			printw("%s\t", gfileTable[id - 1].name);
		else
			_BOLD(printw("%s\t", gdirTable[0 - id].name));
	}
	printw("\n");
	refresh();
}
