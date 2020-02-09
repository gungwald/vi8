#include <string.h>	/* strncpy */
#include <stdlib.h>	/* malloc */

#include "editbuffer.h"

static FILE *f;

struct EditBuffer *ebInit(struct EditBuffer *b)
{
    	b->length = 0;
	return b;
}

char *ebToString(struct EditBuffer *b, uint16_t index)
{
	char *result;
	size_t requiredSize; 
	
	requiredSize = b->lines[index].length + 1;
	result = malloc(sizeof(char) * requiredSize);
	if (result != NULL) 
		strncpy(result, b->lines[index].data, requiredSize);

	return result;
}

struct EditBuffer *ebLoad(struct EditBuffer *b, const char *filename)
{
        f = fopen(filename, "r");
        if (f != NULL) {
                ebReadAllLines(b, f);
                fclose(f);
        }
	return b;
}

bool ebIsFull(struct EditBuffer *b)
{
        return b->length >= EB_MAX_LEN;
}

struct EditBuffer *ebReadAllLines(struct EditBuffer *b, FILE *f)
{
        ebInit(b);
        while (!feof(f) && !ferror(f) && !ebIsFull(b))
                ebReadLine(b, f);
        return b;
}

struct EditBuffer *ebReadLine(struct EditBuffer *b, FILE *f)
{
        int c;
        uint8_t i = 0;
        uint8_t lineIndex;
        char *data;
        struct Line *line;

        lineIndex = b->length;
        line = &(b->lines[lineIndex]);
        data = line->data;
        while (i < EB_MAX_LINE_LEN && (c = getc(f)) != EOF && c != '\r')
                data[i++] = c;

        if (ferror(f))
                perror("Read failed");

        line->length = i;
        ++(b->length);
        return b;
}

