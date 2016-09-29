cmdList = open('commands/commands.list')
includeList = open('commands/include_cmds.h', 'w')
initList = open('commands/init_list.c', 'w')
i = 0
for line in cmdList:
    includeList.write('#include "' + line.rstrip() + '.c"\n')
    initList.write('strcpy(cmds['+ str(i) + '].name, "' + line.rstrip() + '");\n')
    initList.write('cmds[' + str(i) + '].func = &_' + line.rstrip() + ';\n');
    i += 1
includeList.write('#define NUM_OF_CMDS ' + str(i) + '\n')
includeList.close()
initList.close()
cmdList.close()
