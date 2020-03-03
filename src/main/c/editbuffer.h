#ifndef EDITBUFFER_H_LKJASDFLKJASDFLK
#define EDITBUFFER_H_LKJASDFLKJASDFLK

/* External Modules */
#include <stdio.h>      /* FILE */
#include <stdbool.h>	/* bool */
#include <stdint.h>	/* uint8_t, uint16_t */

/* Constants */
#define EB_MAX_LEN      200
#define EB_MAX_LINE_LEN 80

struct Line
{
	char data[EB_MAX_LINE_LEN];
	uint8_t length;
};

/* Types */
struct EditBuffer
{
	/* Basically a 2-dim array but also stores the length of each line.*/
	struct Line lines[EB_MAX_LEN];

	/* Line count */
	uint16_t lineCount;

	uint8_t  cursorX; /* 0-based */
	uint16_t cursorY; /* 0-based */
};

/* Function Frototypes */
extern struct EditBuffer *ebInit(struct EditBuffer *eb);
extern struct EditBuffer *ebLoad(struct EditBuffer *eb, const char *filename);
extern bool ebIsFull(struct EditBuffer *eb);
extern struct EditBuffer *ebReadAllLines(struct EditBuffer *eb, FILE *f);
extern struct EditBuffer *ebReadLine(struct EditBuffer *eb, FILE *f);
extern char *ebGetLineCopy(struct EditBuffer *eb, uint16_t zeroBasedIndex);
extern struct EditBuffer* ebAppendLineCopy(struct EditBuffer *eb, const char *line);
extern struct EditBuffer *ebCursorRight(struct EditBuffer *eb);
extern struct EditBuffer *ebCursorLeft(struct EditBuffer *eb);


#endif

