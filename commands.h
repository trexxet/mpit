#ifndef COMMANDS_H_
#define COMMANDS_H_

typedef void (*cmdFunc_t)();

typedef struct {
	char name[32];
	cmdFunc_t func;
} cmd_t;

#endif
