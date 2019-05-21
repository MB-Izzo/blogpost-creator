utils.o: utils.c utils.h
	gcc -c utils.c

main.o: main.c utils.h
	gcc -c main.c

blogpost: main.o utils.o
	gcc main.o utils.o -o blogpost
