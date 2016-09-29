void _cd()
{
	uint16_t newDirID;
	exists(args, &newDirID) ? playerData.dir = newDirID : printw("Can't find such directory\n");
}
