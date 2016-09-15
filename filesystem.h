#pragma once

typedef struct {
	char name[MAX_NAME_LEN];
	uint16_t id;
	uint8_t isdir;
	char content[MAX_FILE_LEN];
	int16_t parent;
	int16_t childs[MAX_FILE_DIR];
	uint8_t childnum;
} gfile_t;

typedef struct {
	uint16_t IDs[128];
	uint8_t top;
} gdirIDStack;
