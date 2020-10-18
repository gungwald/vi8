#include <stdio.h>   /* FILE, fopen, gets, fclose */
#include <stdbool.h> /* true, false */
#include <stdint.h>  /* uint8_t, uint16_t */
#include <conio.h>   /* screensize */

#include "editbuffer.h"
#include "globals.h"

static char fname[100];

void main(int argc, char *argv[])
{
    ebInit(&b);
    screensize(&screenWidth, &screenHeight);
    if (argc > 1) {
    	ebOpenFile(argv[1]);
    }
    else {
    	printf("File:");
    	fgets(fname, sizeof(fname), stdin);
    }
}

