#ifndef FILESYSTEM_H_
#define FILESYSTEM_H_

#define MAX_DIRS 1024
#define MAX_FILES 1024
#define MAX_NAME_LEN 32
#define MAX_FILE_LEN 2048
#define MAX_FILE_DIR 32

typedef struct {
	char name[MAX_NAME_LEN];
	char cont[MAX_FILE_LEN];
	int16_t parent;
	uint16_t id;
} gfile;

typedef struct {
	char name[MAX_NAME_LEN];
	int16_t parent;
	int16_t childs[MAX_FILE_DIR];
	uint8_t childnum;
	int16_t id;
} gdir;

typedef struct {
	int16_t IDs[128];
	uint8_t top;
} gdirIDStack;

#endif
