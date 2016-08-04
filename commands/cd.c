void cd()
{
	char *name = strtok(NULL, "");
	int16_t newDirID;
	dirExists(name, &newDirID) ? playerData.dir = newDirID : printw("Can't find such directory\n");
}
