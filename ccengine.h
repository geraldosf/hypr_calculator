

struct display {
	char string[32];
	int len;
};

struct calculator {
	struct display dp;
	int cx;
};

void displayAppend(struct display *dp, const char c);

void displayPop(struct display *dp);

