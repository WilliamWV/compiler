#include "../../include/hash.h"
#include "../../include/util.h"

struct lexval* temp;

int main(){
	printf("Inicializando l1 ...\n");
	ILOC_LIST* l1 = createILOCList();
	printf("l1 tem %d operações\n", l1->operations);
	printf("Adicionando operação add r0, r1 => r2\n");
	ILOC_OP* add = createILOCOper(ADD, "add");
	printf("operação \'%s\' adicionada com opcode = %d, possuindo %d argumentos\n", add->opSpelling, add->opcode, add->argsNum);
	printf("criando argumentos da operação ...\n");	
	ILOC_ARG* r0 = createILOCArg(REG, "r0");
	printf("argumento \'%s\' adicionado, tipo = %d\n", r0->value.str, r0->argType);
	printf("adicionando argumento \'%s\' na operação \'%s\'\n", r0->value.str, add->opSpelling);
	addILOCArg(add, r0);
	printf("Operação \'%s\' tem %d argumentos, o primeiro é %s\n", add->opSpelling, add->argsNum, add->args[0]->value.str);
	printf("criando demais argumentos ... \n");	
	ILOC_ARG* r1 = createILOCArg(REG, "r1");
	ILOC_ARG* r2 = createILOCArg(REG, "r2");
	addILOCArg(add, r1);
	addILOCArg(add, r2);
	printf("Operação \'%s\' tem %d argumentos, que são:\n", add->opSpelling, add->argsNum);
	for(int i = 0; i<add->argsNum; i++){
		printf("\t\'%s\'\n", add->args[i]->value.str);
	}
	
	printf("Adicionando operação \'%s\' à l1 ...\n", add->opSpelling);
	addILOCToList(l1, add);
	printf("l1 tem %d operações, a primeira é:\'%s\' que tem %d argumentos\n", l1->operations, l1->list[0]->opSpelling, l1->list[0]->argsNum);	
	
	printf("Adicionando operação addI  r3, 3 => r4\n");
	ILOC_OP* addI = createILOCOper(ADDI, "addI");
	ILOC_ARG* r3 = createILOCArg(REG, "r3");
	int tres = 3;
	ILOC_ARG* c3 = createILOCArg(IMED, (void*) &tres);
	ILOC_ARG* r4 = createILOCArg(REG, "r4");
	
	addILOCArg(addI, r3);
	addILOCArg(addI, c3);
	addILOCArg(addI, r4);
	addILOCToList(l1, addI);
	printf("adicionou \'%s\' a l1\n", l1->list[1]->opSpelling);
	printILOCList(l1);
	
	printf("criando lista l2 como concatenação de l1 consigo mesma\n");
	ILOC_LIST* l2 = concatILOC(l1, l1);
	printf("l2:\n");
	printILOCList(l2);
	printf("criando lista l3 como concatenação de l1 com l2\n");
	ILOC_LIST* l3 = concatILOC(l1, l2);
	
	printf("Adicionando operação divI r1, 12 => r3 em l3\n");	
	int doze = 12;
	createOperation(l3, DIVI, "divI", "r1", (void*) &doze, "r3");
	printf("Adicionando operação load r1 => r2\n");
	createOperation(l3, LOAD, "load", "r1", NULL, "r2");
	printf("Adicionando operação jump -> r1\n");
	createOperation(l3, JUMP, "jump", "r1", NULL, NULL);
	printf("Adicionando operação nop\n");
	createOperation(l3, NOP, "nop", NULL, NULL, NULL);
	printf("Adicionando operação jumpI -> L1\n");
	createOperation(l3, JUMPI, "jumpI", "L1", NULL, NULL);

	printf("l3:\n");
	printILOCList(l3);	
	
	printf("Criando lista l4 para testar cálculo de endereço de variáveis\n");
	ILOC_LIST* l4 = createILOCList();
	
	initTable();	
	//int var1;
	temp = createLexval(1, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, FALSE, 0);
	printf("Inseriu \"int var1;\" em escopo global\n");
	free(temp);
	temp = NULL;

	initTable();
	temp = createLexval(17, IDS, NONE, "var2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, FALSE, 0);
	printf("Inseriu \"int var2;\" em escopo local\n");
	free(temp);
	temp = NULL;
	temp = createLexval(17, IDS, NONE, "var3", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, FALSE, 0);
	printf("Inseriu \"int var3;\" em escopo local\n");
	free(temp);
	temp = NULL;

	char* reg1 = loadVarToRegister(l4, "var1");
	printf("carregou var1 em registrador %s\n", reg1);	
	char* reg2 = loadVarToRegister(l4, "var2");
	printf("carregou var2 em registrador %s\n", reg2);	
	char* reg3 = loadVarToRegister(l4, "var3");
	printf("carregou var3 em registrador %s\n", reg3);	
	
	
	closeTable();
	closeTable();
	printf("l4:\n");
	printILOCList(l4);

	liberaTudo();
	printf("Teste concluído\n");
}
