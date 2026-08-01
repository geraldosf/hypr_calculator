#include "ccengine.h"

void displayAppend(struct display *dp, const char c){
	dp->string[dp->len] = c;
	dp->len++;
}

void displayPop(struct display *dp){
	dp->string[dp->len] = '\0';
	dp->len--;
}
