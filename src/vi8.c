#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <conio.h>

extern void writeWithAsm(void);

#define NORMAL(ch) (ch | 0x80)
#define SCREEN_WIDTH 40
#define SCREEN_HEIGHT 24

const char *lineAddresses[] = { (char *) 0x400, (char *) 0x480, (char *) 0x500,
		(char *) 0x580, (char *) 0x600, (char *) 0x680, (char *) 0x700,
		(char *) 0x780, (char *) 0x428, (char *) 0x4A8, (char *) 0x528,
		(char *) 0x5A8, (char *) 0x628, (char *) 0x6A8, (char *) 0x728,
		(char *) 0x7A8, (char *) 0x450, (char *) 0x4D0, (char *) 0x550,
		(char *) 0x5D0, (char *) 0x650, (char *) 0x6D0, (char *) 0x750,
		(char *) 0x7D0 };

uint8_t cursorX = 0;
uint8_t cursorY = 0;

uint8_t bufferX = 0;
uint16_t bufferY = 0;

void writeWithConio(void);
void writeToMemoryArray(void);
void writeToMemory(void);

void main(void) {
	int i;

	cursor(1);
	for (i = 0; i < 5; ++i) {
		clrscr();
		writeWithConio();
		cputs("conio - Press a key to continue"); cgetc();
	}
	for (i = 0; i < 5; ++i) {
		clrscr();
		writeToMemoryArray();
		cputs("memoryArray - Press a key to continue"); cgetc();
	}
	for (i = 0; i < 5; ++i) {
		clrscr();
		writeToMemory();
		cputs("memory - Press a key to continue"); cgetc();
	}
	for (i = 0; i < 5; ++i) {
		clrscr();
		writeWithAsm();
		cputs("asm - Press a key to continue"); cgetc();
	}
	clrscr();
}

void writeWithConio(void) {
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

void writeToMemoryArray(void) {
	char *startAddress;
	char c;
	uint8_t line;
	uint8_t column;

	for (line = 0; line < SCREEN_HEIGHT; ++line) {
		c = NORMAL(line + 0x40);
		startAddress = (char *) lineAddresses[line];
		for (column = 0; column < SCREEN_WIDTH; ++column) {
			startAddress[column] = c;
		}
	}
}

void writeToMemory(void) {
	char *addr;
	char c;
	register uint8_t line;
	register uint8_t column;
	char **lineAddress;

	lineAddress = (char **) lineAddresses;
	for (line = 0; line < SCREEN_HEIGHT; ++line) {
		c = NORMAL(line + 0x40);
		addr = *lineAddress;
		for (column = 0; column < SCREEN_WIDTH; ++column) {
			*addr = c;
			++addr;
		}
		++lineAddress;
	}
}

void displayLine(uint16_t bufferLine, uint8_t screenLine) {
	char *screenLineAddress = (char *) lineAddresses[screenLine];
}
