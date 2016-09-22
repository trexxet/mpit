strcpy(cmds[0].name, "cat");
cmds[0].func = &cat;
strcpy(cmds[1].name, "cd");
cmds[1].func = &cd;
strcpy(cmds[2].name, "ls");
cmds[2].func = &ls;
strcpy(cmds[3].name, "quit");
cmds[3].func = &quit;
