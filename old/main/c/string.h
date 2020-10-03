/*
 * string.h
 *
 *  Created on: Mar 3, 2020
 *      Author: wlc29
 */

#ifndef SRC_MAIN_C_STRING_H_MZNXNCBVNXZM
#define SRC_MAIN_C_STRING_H_MZNXNCBVNXZM

#include <stdio.h>
#include <stdint.h>

#define STRING_MAX_LENGTH 255

typedef uint8_t StringLength;

struct String {
	char data[STRING_MAX_LENGTH];
	StringLength length;
};

extern struct String *sInit(struct String *s);
extern struct String *sCopy(struct String *dest, struct String *src);
extern struct String *sCopyCharPtr(struct String *dest, const char *src);
extern StringLength sLength(struct String *s);
extern struct String *sConcat(struct String *dest, struct String *src);
extern struct String *sConcatCharPtr(struct String *dest, const char *src);
extern struct String *sConcatChar(struct String *dest, char src);
extern struct String *sReadLine(FILE *src, struct String *dest);
extern void sWriteLine(FILE *dest, struct String *src);


#endif
