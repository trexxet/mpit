int _echo_parseFlags(char* arg, int* nflag, int* eflag, int arglen);
void _echo_parseString(char* arg, int eflag, int arglen);

void _echo()
{
	int	argcount = 1,	// counter for arguments	
		flagmode = 1,	// if 1, then search for flags
		nflag = 0,	// -n flag
		eflag = 0;	// -e and -E flags
	char* arg;
	while (arg = strtok_r(args, " '", &args))
	{
		int arglen = strlen(arg);
		// PARSE ARGUMENTS
		if (flagmode)
			flagmode = _echo_parseFlags(arg, &nflag, &eflag, arglen);
		// PARSE STRINGS
		if (!flagmode)
		{
			_echo_parseString(arg, eflag, arglen);
			addch(' ');
		}
	}
	if (!nflag)
		addch('\n');
}

int _echo_parseFlags(char* arg, int* nflag, int* eflag, int arglen)
{
	if (arg[0] != '-' || arglen <= 1)
		return 0;
	for (int i = 1; i < arglen; i++)
		switch (arg[i])
		{
			case 'n':
				*nflag = 1;
				break;
			case 'e':
				*eflag = 1;
				break;
			case 'E':
				*eflag = 0;
				break;
			default:
				return 0;
		}
	return 1;
}

void _echo_parseString(char* arg, int eflag, int arglen)
{
	int escapeChar = 0;
	for (int i = 0; i < arglen; i++)
	{
		if (escapeChar)
		{
			switch (arg[i])
			{
				case '\\':
					addch('\\');
					break;
				case 'n':
					addch('\n');
					break;
				case 't':
					addch('\t');
					break;
				case 'v':
					addch('\v');
					break;
				default:
					addch('\\');
					addch(arg[i]);
					break;
			}
			escapeChar = 0;
		}
		else
		{
			if (arg[i] == '\\' && eflag)
				escapeChar = 1;
			else
				addch(arg[i]);
		}
	}
}
