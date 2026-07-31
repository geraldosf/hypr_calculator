#include <unistd.h>
#include <termios.h>

void enableRawMode(){
	struct termios raw;

	tcgetattr(STDIN_FILENO, &raw);

	raw.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON);
	raw.c_oflag &= ~OPOST;
	raw.c_lflag &= ~(ECHO | ECHONL | ICANON | ISIG | IEXTEN);
	raw.c_cflag &= ~(CSIZE | PARENB);
	raw.c_cflag |= CS8;

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main(){

	enableRawMode();

	while(1){

	}
	
}
