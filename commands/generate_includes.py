cmdList = open('commands/commands.list')
initList = open('commands/init_list.c', 'w')
_includeList = []
i = 0
for line in cmdList:
    _includeList.append('#include "' + line.rstrip() + '.c"\n')
    initList.write('strcpy(cmds['+ str(i) + '].name, "' + line.rstrip() + '");\n')
    initList.write('cmds[' + str(i) + '].func = &_' + line.rstrip() + ';\n')
    i += 1
initList.close()
cmdList.close()
_includeList.insert(0, '#define NUM_OF_CMDS ' + str(i) + '\n')
_includeList.insert(1, 'cmd_t cmds[NUM_OF_CMDS];\n')
includeList = open('commands/include_cmds.h', 'w')
for line in _includeList:
    includeList.write(line)
includeList.close()
