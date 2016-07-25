strcpy(cmds[0].name, "cd");
cmds[0].func = &cd;
strcpy(cmds[1].name, "ls");
cmds[1].func = &ls;
strcpy(cmds[2].name, "cat");
cmds[2].func = &cat;
