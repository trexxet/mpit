all:
	python3 commands/generate_includes.py
	gcc main.c game.c login.c filesystem.c commands.c terminal.c -g -o mpit -lncursesw
	./mpit
