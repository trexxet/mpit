void _help()
{
	_BOLD(printw("MPIT System commands\n"));
	for (int i = 0; i < NUM_OF_CMDS; i++)
		printw("\t%s\n", cmds[i].name);
}
