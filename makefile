NAME = Main

all:
	gcc -Ofast -o bin/$(NAME).exe src/*.c -I include -L lib

debug:
	gcc -o bin/$(NAME)DEBUG.exe src/*.c -D DEBUG -I include -L lib
