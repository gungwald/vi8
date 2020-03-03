#include <string.h>	/* strncpy */
#include <stdlib.h>	/* malloc */

#include "editbuffer.h"

static FILE *f;

struct EditBuffer* ebInit(struct EditBuffer *b)
{
	b->lineCount = 0;
	b->cursorX = 0;
	b->cursorY = 0;
	return b;
}

char* ebGetLineCopy(struct EditBuffer *b, uint16_t index)
{
	char *result;
	size_t requiredSize;

	requiredSize = b->lines[index].length + 1;
	result = malloc(sizeof(char) * requiredSize);
	if (result != NULL)
		strcpy(result, b->lines[index].data);

	return result;
}

struct EditBuffer* ebLoad(struct EditBuffer *b, const char *filename)
{
	f = fopen(filename, "r");
	if (f != NULL)
	{
		ebReadAllLines(b, f);
		fclose(f);
	}
	return b;
}

bool ebIsFull(struct EditBuffer *b)
{
	return b->lineCount >= EB_MAX_LEN;
}

struct EditBuffer* ebReadAllLines(struct EditBuffer *b, FILE *f)
{
	ebInit(b);
	while (!feof(f) && !ferror(f) && !ebIsFull(b))
		ebReadLine(b, f);
	return b;
}

struct EditBuffer* ebReadLine(struct EditBuffer *b, FILE *f)
{
	int c;
	uint8_t i = 0;
	uint8_t lineIndex;
	char *data;
	struct Line *line;

	if (b->lineCount < EB_MAX_LEN)
	{
		lineIndex = b->lineCount;
		line = &(b->lines[lineIndex]);
		data = line->data;
		while (i < EB_MAX_LINE_LEN && (c = getc(f)) != EOF && c != '\r')
			data[i++] = c;

		if (ferror(f))
			perror("Read failed");

		line->length = i;
		++(b->lineCount);
	}
	else
	{
		fprintf(stderr, "EditBuffer is full");
	}
	return b;
}

struct EditBuffer* ebAppendLineCopy(struct EditBuffer *b, const char *line)
{
	struct Line *destLine;
	char *destData;

	if (b->lineCount < EB_MAX_LEN)
	{
		destLine = &(b->lines[b->lineCount]);
		destData = destLine->data;
		strncpy(destData, line, EB_MAX_LINE_LEN + 1);
		destData[EB_MAX_LINE_LEN]; /* Required fail-safe */
		destLine->length = strlen(destData);
		++(b->lineCount);
	}
	else
	{
		fprintf(stderr, "EditBuffer is full");
	}
	return b;
}

struct EditBuffer *ebCursorRight(struct EditBuffer *eb)
{
	unsigned char x;

	x = wherex();
	if (x < screenWidth-1) {
		x--;
		gotox(x);
		eb->cursorX = x;
	}
	return eb;
}

struct EditBuffer *ebCursorLeft(struct EditBuffer *eb)
{
	unsigned char x;

	/* x is unsigned so must stay 0 or greater. */
	x = wherex();
	if (x > 0) {
		x--;
		gotox(x);
		eb->cursorX = x;
	}
	else {
		beep();
	}
	return eb;
}
