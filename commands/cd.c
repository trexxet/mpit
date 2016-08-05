void cd()
{
	char *name = strtok(NULL, "");
	uint16_t newDirID;
	exists(name, &newDirID) ? playerData.dir = newDirID : printw("Can't find such directory\n");
}
