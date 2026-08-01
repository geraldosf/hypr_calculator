#include <unistd.h>
#include <termios.h>
#include <stdlib.h>
#include "ccengine.h"

struct termios orig_termios;

struct calculator calc;


enum editorKeys {
	ARROW_UP = 1000,
	ARROW_DOWN,
	ARROW_LEFT,
	ARROW_RIGHT,
	ENTER,
	BACKSPACE,
};

void disableRawMode() {
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}

void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);

	struct termios raw = orig_termios;

	atexit(disableRawMode);

	raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	raw.c_oflag &= ~OPOST;
	raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	raw.c_cflag &= ~(CSIZE | PARENB);
	raw.c_cflag |= CS8;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

char editorReadKey() {
	char c;
	read(STDIN_FILENO, &c, 1);

	return c;
}

void editorProcessKeypress(){
	char c = editorReadKey();
	
	switch (c) {
		case 'q':
			exit(0);
			break;
		default:
			displayAppend(&calc.dp, c);
			break;
	}
}

void initCalculator() {
	calc.cx = 0;
	calc.dp.len = 0;
}

void refreshScreen() {
	write(STDOUT_FILENO, "\x1b[2J", 4);
	write(STDOUT_FILENO, "\x1b[H", 3);
	write(STDOUT_FILENO, calc.dp.string, calc.dp.len);
}

int main(){

	enableRawMode();
	initCalculator();

	while (1) {
		refreshScreen();
		editorProcessKeypress();
	}
	
}
