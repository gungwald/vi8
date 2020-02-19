#include <stdio.h>   /* FILE, fopen, gets, fclose */
#include <stdbool.h> /* true, false */
#include <stdint.h>  /* uint8_t, uint16_t */
#include <conio.h>   /* screensize */

#include "editbuffer.h"

/* type */
enum ReturnStatus {FAILURE, SUCCESS, EOF_REACHED};

/* var */
struct EditBuffer b;
unsigned char screenWidth;
unsigned char screenHeight;

void main()
{
    ebInit(&b);
    screensize(&screenWidth, &screenHeight);
}

