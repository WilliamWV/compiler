#ifndef NAMING_H
#define NAMING_H "namingh"
#include "everybodyHateLeaks.h"
//#include "functionArgs.h"

typedef struct listOfRegisters{
	int numberOfRegs;
	char **registers;
} Registers;

char* getNewRegister();
char* getNewLabel();
void addNewRegister(char *reg, char *funcName);

#endif
