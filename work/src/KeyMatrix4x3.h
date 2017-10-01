#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#define ROWS 4
#define COLUMNS 3

typedef struct {
	int rows;
	int columns;
	int keyState[ROWS][COLUMNS];
	int keyMapping[ROWS][COLUMNS];
	int rowPin[ROWS], columnPin[COLUMNS];
	int keyPressed;		// Zeigt an, ob seid dem letzten aufruf von scanKeys() eine Taste gedrückt wurde.
	int lastPressed;	// Zeigt an, welche Taste waehrend dem letzten aufruf von scanKeys() gedrueckt war.

} KeyMatrix;

int init(KeyMatrix* KM);

int scanKeys(KeyMatrix* KM);

int waitForRelease(KeyMatrix* KM);
