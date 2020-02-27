/**
 * controller.c
 *
 *  Created on: Feb 25, 2020
 *      Author: wlc29
 */

#include <stdbool.h>
#include <conio.h>

char key;

void commandMode(struct EditBuffer *eb)
{
	cursor(true);
	key = cgetc();
}
