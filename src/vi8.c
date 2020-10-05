#include <stdint.h>

#define NORMAL(ch) (ch | 0x80)
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

const char *lineAddresses[] = {
    (char *) 0x400, (char *) 0x480, (char *) 0x500, (char *) 0x580, 
    (char *) 0x600, (char *) 0x680, (char *) 0x700, (char *) 0x780, 
    (char *) 0x428, (char *) 0x4A8, (char *) 0x528, (char *) 0x5A8, 
    (char *) 0x628, (char *) 0x6A8, (char *) 0x728, (char *) 0x7A8, 
    (char *) 0x450, (char *) 0x4D0, (char *) 0x550, (char *) 0x5D0,
    (char *) 0x650, (char *) 0x6D0, (char *) 0x750, (char *) 0x7D0 
};

uint8_t cursorX = 0;
uint8_t cursorY = 0;

uint8_t bufferX = 0;
uint16_t bufferY = 0;

void main(void)
{
    char c;
    uint8_t line;
    char *cellAddress;
    const char *startAddress;
    const char *endAddress;

    for (line = 0; line < SCREEN_HEIGHT; ++line) {
        startAddress = lineAddresses[line];
	endAddress = startAddress + SCREEN_WIDTH;
    	c = NORMAL(line + 0x40);
        for (cellAddress = (char *) startAddress; cellAddress < endAddress; ++cellAddress) {
            *cellAddress = c;
	}
    }
}

void displayLine(uint16_t bufferLine, uint8_t screenLine)
{
    const char *screenLineAddress = lineAddresses[screenLine];
}
