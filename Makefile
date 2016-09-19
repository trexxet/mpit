CC = gcc
PYTHON = python3
TARGET = mpit

CSRC = main.c game.c login.c filesystem.c shell.c
PYSRC = commands/generate_includes.py
CFLAGS = -g -O0 --std=gnu11
LDLIBS = -lncursesw

BIN = /usr/local/games
DATA = /usr/local/games/mpit_data
FILESYS = $(DATA)/filesystem
SAVES = $(DATA)/saves

all:
	$(PYTHON) $(PYSRC)
	$(CC) $(CSRC) -o $(TARGET) $(CFLAGS) $(LDLIBS)
	@echo 'OK, now go for make install'

install:
	install $(TARGET) $(BIN)
	mkdir $(DATA) $(FILESYS) $(SAVES)
	cp bootlogo $(DATA)
	cp -r filesystem/* $(FILESYS)
	chmod -R o+w $(DATA)
	@echo 'Nice, now you can play mpit'

uninstall:
	rm $(BIN)/$(TARGET)
	rm -rf $(DATA)
	@echo 'Uninstalled :^('
