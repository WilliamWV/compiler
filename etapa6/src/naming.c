////////////////////////////////////////////////////////////////////////////////
/// Nomeação de rótulos e de registradores                                   ///
/// Segue as convenções estabelecidas na especificação, ou seja:             ///
///                                                                          ///
/// Registradores:                                                           ///
///   - Começam pela letra 'r' minúscula seguida de um número inteiro        /// 
///     positivo                                                             ///
/// Rótulos:                                                                 ///
///   - Começam pela letra 'L' maiúscula seguida de um número inteiro        ///
///     positivo                                                             ///
////////////////////////////////////////////////////////////////////////////////

#include "../include/naming.h"
#include "../include/functionArgs.h"

int currentRegister = 0;
int currentLabel = 0;
extern char *currentFunc;

//Retorna a quantidade de digitos que um valor inteiro possui
//poderia ser feito com funções logaritmicas, mas para manter a simplicidade
//e evitar precisões desnecessárias, nesse caso, foi usado um laço

int digitsOfInt(int val){
	int digits = 0;	
	do{
		val /= 10;
		digits++;
	}while(val!=0);

	return digits;
}



char* getNewRegister(){

	int digits = digitsOfInt(currentRegister);
	int temp = currentRegister;
	char* reg = (char*) aloca(sizeof(digits + 1 + 1));
	reg[0] = 'r';
	for(int i = digits; i>0; i--){
		reg[i] = '0' + temp % 10;
		temp /= 10;
	}
	reg[digits + 1] = '\0';
	addNewRegister(reg, currentFunc);
	currentRegister++;
	return reg;
}

char* getNewLabel(){
	int digits = digitsOfInt(currentLabel);
	int temp = currentLabel;

	char* lab = (char*) aloca(sizeof(digits + 1 + 1));
	lab[0] = 'L';
	for(int i = digits; i>0; i--){
		lab[i] = '0' + temp % 10;
		temp /= 10;
	}
	lab[digits + 1] = '\0';
	currentLabel++;
	return lab;
}

void addNewRegister(char *reg, char *funcName){
	Hash* funcContent = getSymbol(funcName);
	if(funcContent != NULL){
		funcContent->registers->numberOfRegs = funcContent->registers->numberOfRegs + 1;
		funcContent->registers->registers = (char**)realoca(funcContent->registers->registers, funcContent->registers->numberOfRegs * sizeof(char*));
		funcContent->registers->registers[funcContent->registers->numberOfRegs - 1] = reg;
	}
}
