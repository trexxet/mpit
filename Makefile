CC = gcc
PYTHON = python3
TARGET = mpit

CSRC = main.c game.c login.c filesystem.c commands.c terminal.c
PYSRC = commands/generate_includes.py
CFLAGS = -g -lncursesw

BIN = /usr/local/bin
DATA = ~/.mpit
FILESYS = $(DATA)/filesystem
SAVES = $(DATA)/saves

all:
	$(PYTHON) $(PYSRC)
	$(CC) $(CSRC) -o $(TARGET) $(CFLAGS)

install:
	install $(TARGET) $(BIN)
	mkdir $(DATA) $(FILESYS) $(SAVES)
	cp bootlogo $(DATA)
	cp -r filesystem/* $(FILESYS)
	chmod -R o+w $(DATA)

uninstall:
	rm $(BIN)/$(TARGET)
	rm -rf $(DATA)
