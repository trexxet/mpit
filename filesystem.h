#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#define MAX_DIRS 1024
#define MAX_FILES 1024
#define MAX_NAME_LEN 32
#define MAX_FILE_LEN 2048
#define MAX_FILE_DIR 32

typedef struct {
	char name[MAX_NAME_LEN];
	uint16_t id;
	uint8_t isdir;
	char content[MAX_FILE_LEN];
	int16_t parent;
	int16_t childs[MAX_FILE_DIR];
	uint8_t childnum;
} gfile;

typedef struct {
	uint16_t IDs[128];
	uint8_t top;
} gdirIDStack;

#endif
