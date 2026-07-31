#include <unistd.h>
#include <termios.h>
#include <stdlib.h>

struct termios orig_termios;


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
	}
}

int main(){

	enableRawMode();

	while (1) {
		editorProcessKeypress();
	}
	
}
