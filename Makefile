calculator: ccengine main
	gcc ccengine.o main.o -o calculator 
ccengine:
	gcc ccengine.c -Wall -Wextra -std=c17 -c
main:
	gcc main.c -Wall -Wextra -std=c17 -c

