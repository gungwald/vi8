#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>

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

void writeWithConio(void);
void writeToMemory(void);

void main(void)
{
    int i;
    time_t startTime, middleTime, endTime;

    startTime = time(NULL);
    for (i = 0; i < 10; ++i) {
    	clrscr();
    	writeWithConio();
    }
    middleTime = time(NULL);
    for (i = 0; i < 10; ++i) {
    	clrscr();
    	writeToMemory();
    }
    endTime = time(NULL);
    clrscr();
    printf("%lu\n%lu\n%lu\n", 
		    startTime, 
		    middleTime, 
		    endTime);
    printf("conio_time=%lu mem_time=%lu\n", 
		    middleTime - startTime,
		    endTime - middleTime);
}

void writeWithConio(void)
{
    char c;
    uint8_t line;
    uint8_t col;

    for (line = 0; line < SCREEN_HEIGHT; ++line) {
    	c = NORMAL(line + 0x40);
        for (col = 0; col < SCREEN_WIDTH; ++col) {
            cputcxy(col, line, c);
	}
    }
}

void writeToMemory(void)
{
    char c;
    uint8_t line;
    char *cellAddress;
    char *startAddress;
    char *endAddress;

    for (line = 0; line < SCREEN_HEIGHT; ++line) {
        startAddress = (char *) lineAddresses[line];
	endAddress = startAddress + SCREEN_WIDTH;
    	c = NORMAL(line + 0x40);
        for (cellAddress = startAddress; cellAddress < endAddress; ++cellAddress) {
            *cellAddress = c;
	}
    }
}

void displayLine(uint16_t bufferLine, uint8_t screenLine)
{
    char *screenLineAddress = (char *) lineAddresses[screenLine];
}
