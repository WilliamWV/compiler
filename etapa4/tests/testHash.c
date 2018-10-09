#include "../include/util.h"
#include "../include/natureza.h"
#include <stdlib.h>
#include <stdio.h>
/**
	O objetivo desse arquivo é testar as seguintes funções:
	  * void initTable();
	  * void closeTable();
	  * void addSymbol(struct lexval* valor_lexico, int nature, int type);
	  * void addFuncArg(char* symbol, FuncArg* arg);
	  * void addField(char* symbol, UserTypeField* utf);l
	  * Hash* getSymbol(char* symbol);
*/

struct lexval* temp;
void multiTableTest(){
	printf("Inicializando tabela global...\n");
	initTable();
	
	 
	temp = createLexval(1, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT);
	printf("Inseriu \"int var1;\"\n");
	free(temp);
	temp = NULL;
	
	temp = createLexval(12, IDS, NONE, "var3", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING);
	printf("Inseriu \"string var3;\"\n");
	free(temp);
	temp = NULL;

	printf("Inicializando tabela local...\n");
	initTable();
	
	temp = createLexval(17, IDS, NONE, "var2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT);
	printf("Inseriu \"float var2;\"\n");
	free(temp);
	temp = NULL;

	//símbolo deve ocultar o símbolo var1 global	
	temp = createLexval(21, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING);
	printf("Inseriu \"string var1;\"\n");
	free(temp);
	temp = NULL;

	Hash* v1= getSymbol("var1");
	if(v1 != NULL){
		printf("Encontrou var1 ");
		if(v1->type == STRING) {printf("string - id local\n");}
		else if(v1->type == INT) {printf("int - id global\n");}
	}
	else {printf("não encontrou var1\n");}
	if(getSymbol("var2") != NULL){printf("Encontrou var2\n");}
	else {printf("não encontrou var2\n");}
	if(getSymbol("var3") != NULL){printf("Encontrou var3\n");}
	else {printf("não encontrou var3\n");}
		
	printf("Fechando tabela local...\n");
	closeTable();

	v1= getSymbol("var1");
	if(v1 != NULL){
		printf("Encontrou var1 ");
		if(v1->type == STRING) {printf("string - id local\n");}
		else if(v1->type == INT) {printf("int - id global\n");}
	}
	else {printf("não encontrou var1\n");}
	if(getSymbol("var2") != NULL){printf("Encontrou var2\n");}
	else {printf("não encontrou var2\n");}
	if(getSymbol("var3") != NULL){printf("Encontrou var3\n");}
	else {printf("não encontrou var3\n");}
	
	printf("Fechando tabela global...\n");
	closeTable();

}
void oneTableTest(){
	printf("Inicializando tabela...\n");
	initTable();
	
	printf("Inserindo símbolos ...\n");
	
	//int var1;
	temp = createLexval(1, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT);
	printf("Inseriu \"int var1;\"\n");
	free(temp);
	temp = NULL;
	
	//float var2;
	temp = createLexval(7, IDS, NONE, "var2", TRUE);	
	addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT);
	printf("Inseriu \"float var2;\"\n");
	free(temp);
	temp = NULL;
	
	//string var3;
	temp = createLexval(12, IDS, NONE, "var3", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING);
	printf("Inseriu \"string var3;\"\n");
	free(temp);
	temp = NULL;
	
	//int foo(int a, const float b);
	temp = createLexval(16, IDS, NONE, "foo", TRUE);	
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT);
	addFuncArg("foo", createFuncArg(INT, NULL, "a", FALSE));
	addFuncArg("foo", createFuncArg(FLOAT, NULL, "b", TRUE));
	printf("Inseriu \"int foo(int a, const float b);\"\n");
	free(temp);
	temp = NULL;
	
	//class animal [protected string name : private int eyes];
	temp = createLexval(21, IDS, NONE, "animal", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, USER);
	addField("animal", createUserTypeField(PROTECTED_ENCAPS, STRING, "name"));
	addField("animal", createUserTypeField(PRIVATE_ENCAPS, INT, "eyes"));
	printf("Inseriu \"class animal [protected string name : private int eyes];\"\n");	
	free(temp);
	temp = NULL;	
	
	//string foo2(userType s)
	temp = createLexval(26, IDS, NONE, "foo2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING);
	addFuncArg("foo", createFuncArg(USER, "userType", "s", FALSE));
	printf("Inseriu \"string foo2(userType s)\"\n");	
	free(temp);
	temp = NULL;

	printf("Buscando símbolos\n");
	
	if(getSymbol("var1") != NULL){printf("Encontrou var1\n");}
	else {printf("não encontrou var1\n");}
	if(getSymbol("var2") != NULL){printf("Encontrou var2\n");}
	else {printf("não encontrou var2\n");}
	if(getSymbol("var3") != NULL){printf("Encontrou var3\n");}
	else {printf("não encontrou var3\n");}
	if(getSymbol("foo") != NULL){printf("Encontrou foo\n");}
	else {printf("não encontrou foo\n");}
	if(getSymbol("animal") != NULL){printf("Encontrou animal\n");}
	else {printf("não encontrou animal\n");}
	if(getSymbol("foo2") != NULL){printf("Encontrou foo2\n");}
	else {printf("não encontrou foo2\n");}
	if(getSymbol("var4") != NULL){printf("Encontrou var4 - Não deveria ter achado\n");}
	else {printf("não encontrou var4 - Como esperado\n");}
	
	printf("Fechando tabela ...\n");
	void closeTable();

}

int main(){
	oneTableTest();
	multiTableTest();
}


