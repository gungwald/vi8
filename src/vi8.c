#include <stdint.h>

#define TXTPG1 ((char *) 0x0400)
#define NORMAL(ch) (ch | 0x80)

char *lineAddresses[] = {
    (char *) 0x400, (char *) 0x480, (char *) 0x500, (char *) 0x580, 
    (char *) 0x600, (char *) 0x680, (char *) 0x700, (char *) 0x780, 
    (char *) 0x428, (char *) 0x4A8, (char *) 0x528, (char *) 0x5A8, 
    (char *) 0x628, (char *) 0x6A8, (char *) 0x728, (char *) 0x7A8, 
    (char *) 0x450, (char *) 0x400, (char *) 0x550, (char *) 0x500,
    (char *) 0x650, (char *) 0x600, (char *) 0x750, (char *) 0x700 
};

uint8_t cursorX = 0;
uint8_t cursorY = 0;

uint8_t bufferX = 0;
uint16_t bufferY = 0;

void main(void)
{
	char *p, *endp;
	char c;

	endp = TXTPG1 + 40;
	c = NORMAL('A');
	for (p = TXTPG1; p < endp; ++p)
		*p = c;
}

void displayLine(bufferLine, screenLine)
{
    char *screenLineAddress = lineAddresses[screenLine];
}
