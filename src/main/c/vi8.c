#include <stdio.h>   /* FILE, fopen, gets, fclose */
#include <stdbool.h> /* true, false */
#include <stdint.h>  /* uint8_t, uint16_t */
#include <conio.h>   /* screensize */

#include "editbuffer.h"
#include "globals.h"

void main()
{
    ebInit(&b);
    screensize(&screenWidth, &screenHeight);
}

