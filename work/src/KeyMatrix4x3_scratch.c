#include <stdio.h>
#include <stdlib.h>

#include <wiringPi.h>

#define ROWS 4
#define COLUMNS 3

typedef struct {
	int rows;
	int columns;
	int keyState[ROWS][COLUMNS];
	int keyMaping[ROWS][COLUMNS];
	int rowPin[ROWS], columnPin[COLUMNS];

} KeyMatrix;

int init(KeyMatrix* KM){

	int i,r,c = 0;
	
	KM->rows = ROWS;
	KM->columns = COLUMNS;

	for(r=0;r<KM->rows;r++){
		for(c=0;c<KM->columns;c++){
			KM->keyState[r][c]=0;
		}
	}

	KM->keyMaping[0][0] = 1;
	KM->keyMaping[0][1] = 2;
	KM->keyMaping[0][2] = 3;

	KM->keyMaping[1][0] = 4;
	KM->keyMaping[1][1] = 5;
	KM->keyMaping[1][2] = 6;

	KM->keyMaping[2][0] = 7;
	KM->keyMaping[2][1] = 8;
	KM->keyMaping[2][2] = 9;

	KM->keyMaping[3][0] = 0;
	KM->keyMaping[3][1] = 0;
	KM->keyMaping[3][2] = 0;

	KM->rowPin[0] = 3;
	KM->rowPin[1] = 4;
	KM->rowPin[2] = 5;
	KM->rowPin[3] = 6;
	
	KM->columnPin[0] = 0;
	KM->columnPin[1] = 1;
	KM->columnPin[2] = 2;
}


int main(int argc, char *argv[]){
	
	KeyMatrix KeyMatrix4x3;

	int i,r,c = 0;
	printf("Start MatrixPad Test\n");
	
	if(wiringPiSetup() != 0)
		printf("ERROR PiSetup()\n");
	else 
		printf("PiSetup succsess\n");

	init(&KeyMatrix4x3);
	
 	for(r=0;r<KeyMatrix4x3.rows;r++){
		pinMode(KeyMatrix4x3.rowPin[r], OUTPUT);
	}

	for(c=0;c<KeyMatrix4x3.columns;c++){
		pinMode(KeyMatrix4x3.columnPin[c], INPUT);		
	}


	for(r=0;r<KeyMatrix4x3.rows;r++){
		
		digitalWrite(KeyMatrix4x3.rowPin[r],1);

		for(c=0;c<KeyMatrix4x3.columns;c++){
			
			if(digitalRead(KeyMatrix4x3.columnPin[c]) == 1)
				KeyMatrix4x3.keyState[r][c]=1;
			else
				KeyMatrix4x3.keyState[r][c]=0;
		}
		 digitalWrite(KeyMatrix4x3.rowPin[r],0);
	}

	for(r=0;r<KeyMatrix4x3.rows;r++){
		for(c=0;c<KeyMatrix4x3.columns;c++){
			printf("%i ",KeyMatrix4x3.keyState[r][c]);
		}
		printf("\n");
	}

	return 0;
}
