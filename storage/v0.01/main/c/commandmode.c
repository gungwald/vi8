/**
 * controller.c
 *
 *  Created on: Feb 25, 2020
 *      Author: wlc29
 */

#include <stdbool.h>
#include <conio.h>
#include "globals.h"
#include "editbuffer.h"

char key;
bool commandModeIsActive;

void commandMode()
{
	cursor(true);
	commandModeIsActive = true;

	while (commandModeIsActive)
	{
		key = cgetc();
		switch (key)
		{
		case 'l':
			ebCursorRight(&eb);
			break;
		case 'h':
			ebCursorLeft(&eb);
			break;
		default:
			break;
		}
	}
}
