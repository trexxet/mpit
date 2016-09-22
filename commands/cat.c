void cat()
{
	uint16_t fileID;
	exists(args, &fileID) ? printw("%s", gfTable[fileID].content) : printw("Can't find such file\n");
}
