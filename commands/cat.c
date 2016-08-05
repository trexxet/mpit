void cat()
{
	char *name = strtok(NULL, "");
	uint16_t fileID;
	exists(name, &fileID) ? printw("%s", gfTable[fileID].content) : printw("Can't find such file\n");
}
