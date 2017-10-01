#include "KeyMatrix4x3.h"

int init(KeyMatrix* KM){
	int i,r,c = 0;
	
	KM->rows = ROWS;
	KM->columns = COLUMNS;

	for(r=0;r<KM->rows;r++){
		for(c=0;c<KM->columns;c++){
			KM->keyState[r][c]=0;
		}
	}
	
	KM->keyPressed = -1;
	KM->lastPressed = -1;

	KM->keyMapping[0][0] = 1;
	KM->keyMapping[0][1] = 2;
	KM->keyMapping[0][2] = 3;

	KM->keyMapping[1][0] = 4;
	KM->keyMapping[1][1] = 5;
	KM->keyMapping[1][2] = 6;

	KM->keyMapping[2][0] = 7;
	KM->keyMapping[2][1] = 8;
	KM->keyMapping[2][2] = 9;

	KM->keyMapping[3][0] = 0;
	KM->keyMapping[3][1] = 0;
	KM->keyMapping[3][2] = 0;

	KM->rowPin[0] = 3;
	KM->rowPin[1] = 4;
	KM->rowPin[2] = 5;
	KM->rowPin[3] = 6;
	
	KM->columnPin[0] = 0;
	KM->columnPin[1] = 1;
	KM->columnPin[2] = 2;
	
	for(r=0;r<KM->rows;r++){
		pinMode(KM->rowPin[r], OUTPUT);
	}

	for(c=0;c<KM->columns;c++){
		pinMode(KM->columnPin[c], INPUT);		
	}
}

int scanKeys(KeyMatrix* KM){
	
	int i,r,c = 0;
	KM->keyPressed=0;										//Zurücksetzten vor dem erneuten scannen
	for(r=0;r<KM->rows;r++){
		
		digitalWrite(KM->rowPin[r],1);

		for(c=0;c<KM->columns;c++){
										
			if(digitalRead(KM->columnPin[c]) == 1){
				if(	KM->keyState[r][c] == 0){				//Wird nur beim Pressen einer Taste gesetzt
					KM->keyPressed=1;
					KM->lastPressed=KM->keyMapping[r][c];}
				KM->keyState[r][c]=1;
			}else
				KM->keyState[r][c]=0;
		}
		 digitalWrite(KM->rowPin[r],0);
	}
	
}

int waitForRelease(KeyMatrix* KM){
	
	while(1){
		scanKeys(KM);
		if(KM->keyPressed == 1)
			return 0;
		usleep(100);
	}
	
}

int main(int argc, char *argv[]){
	
	KeyMatrix KeyMatrix4x3;
	int i= 0;
	printf("Start MatrixPad Test\n");
	
	if(wiringPiSetup() != 0)
		printf("ERROR PiSetup()\n");
	else 
		printf("PiSetup succsess\n");

	init(&KeyMatrix4x3);
	
	for(i=0;i<5;i++){
		waitForRelease(&KeyMatrix4x3);
		printf("KesPressed: %i\n",KeyMatrix4x3.lastPressed);
	}
}
