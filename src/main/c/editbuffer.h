#ifndef EDITBUFFER_H_LKJASDFLKJASDFLK
#define EDITBUFFER_H_LKJASDFLKJASDFLK

/* External Modules */
#include <stdio.h>      /* FILE */
#include <stdbool.h>	/* bool */
#include <stdint.h>	/* uint8_t, uint16_t */

/* Constants */
#define EB_MAX_LEN      200
#define EB_MAX_LINE_LEN 80

/* Types */
struct EditBuffer
{
	/* Basically a 2-dim array but also stores the length of each line.*/
	struct Line
	{
		char data[EB_MAX_LINE_LEN];
		uint8_t length;
	} 
	lines[EB_MAX_LEN];

	/* Line count */
	uint16_t length;

	uint8_t cursorLineIndex;
	uint16_t cursorLine;
};

/* Function Frototypes */
extern struct EditBuffer *ebInit(struct EditBuffer *b);
extern struct EditBuffer *ebLoad(struct EditBuffer *b, const char *filename);
extern bool ebIsFull(struct EditBuffer *b);
extern struct EditBuffer *ebReadAllLines(struct EditBuffer *b, FILE *f);
extern struct EditBuffer *ebReadLine(struct EditBuffer *b, FILE *f);
extern char *ebGetLineCopy(struct EditBuffer *b, uint16_t zeroBasedIndex);
extern struct EditBuffer* ebAppendLineCopy(struct EditBuffer *b, const char *line);


#endif

