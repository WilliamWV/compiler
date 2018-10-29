#include "../../include/naming.h"
#include <stdio.h>

int main(){
	char* r0;
	char* r1;
	char* r2;
	char* r3;
	char* r4;
	char* r5;
	char* r6;
	char* r7;
	char* r8;
	
	
	
	char* l0;
	char* l1;
	char* l2;
	char* l3;
	char* l4;
	char* l5;
	char* l6;
	char* l7;
	char* l8;
	char* l9;
	
	l0 = getNewLabel();
	r0 = getNewRegister();
	l1 = getNewLabel();	
	r1 = getNewRegister();
	l2 = getNewLabel();	
	r2 = getNewRegister();
	l3 = getNewLabel();	
	r3 = getNewRegister();
	l4 = getNewLabel();	
	r4 = getNewRegister();
	l5 = getNewLabel();	
	r5 = getNewRegister();
	l6 = getNewLabel();	
	r6 = getNewRegister();
	l7 = getNewLabel();	
	r7 = getNewRegister();
	l8 = getNewLabel();	
	r8 = getNewRegister();
	l9 = getNewLabel();	

	printf("Labels:\n");
	printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n", l0, l1, l2, l3, l4, l5, l6, l7, l8, l9);

	printf("Registers:\n");
	printf("\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n\t%s\n", r0, r1, r2, r3, r4, r5, r6, r7, r8);


}
