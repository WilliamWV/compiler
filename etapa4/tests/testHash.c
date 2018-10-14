#include "../include/util.h"
#include "../include/userTypeField.h"
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

/**
	Testa se tabela única funciona adequadamente
*/
void oneTableTest(){
	printf("\n\nTESTE DE UMA ÚNICA TABELA\n");
	printf("Inicializando tabela...\n");
	initTable();
	
	printf("Inserindo símbolos ...\n");
	
	//int var1;
	temp = createLexval(1, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, FALSE, STATIC);
	printf("Inseriu \"static int var1;\"\n");
	free(temp);
	temp = NULL;
	
	//float var2;
	temp = createLexval(7, IDS, NONE, "var2", TRUE);	
	addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT, NULL, 0, FALSE, CONST);
	printf("Inseriu \"const float var2;\"\n");
	free(temp);
	temp = NULL;
	
	//string var3;
	temp = createLexval(12, IDS, NONE, "var3", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING, NULL, 0, FALSE, STATIC + CONST);
	printf("Inseriu \"static const string var3;\"\n");
	free(temp);
	temp = NULL;
	
	//int foo(int a, const float b);
	temp = createLexval(16, IDS, NONE, "foo", TRUE);	
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, TRUE, 0);
	addFuncArg("foo", createFuncArg(INT, NULL, "a", FALSE));
	addFuncArg("foo", createFuncArg(FLOAT, NULL, "b", TRUE));
	printf("Inseriu \"int foo(int a, const float b);\"\n");
	free(temp);
	temp = NULL;
	
	//class animal [protected string name : private int eyes];
	temp = createLexval(21, IDS, NONE, "animal", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, USER, NULL, 0, FALSE, 0);
	addField("animal", createUserTypeField(PROTECTED_ENCAPS, STRING, "name"));
	addField("animal", createUserTypeField(PRIVATE_ENCAPS, INT, "eyes"));
	printf("Inseriu \"class animal [protected string name : private int eyes];\"\n");	
	free(temp);
	temp = NULL;	
	
	temp = createLexval(23, IDS, NONE, "dog", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, USER, "animal", 0, FALSE, 0);
	printf("Inseriu \"dog animal;\"\n");	
	free(temp);
	temp = NULL;	
	
	//string foo2(userType s)
	temp = createLexval(26, IDS, NONE, "foo2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING, NULL, 0, TRUE, 0);
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
	if(getSymbol("dog") != NULL){printf("Encontrou dog\n");}
	else {printf("não encontrou dog\n");}
	if(getSymbol("var4") != NULL){printf("Encontrou var4 - Não deveria ter achado\n");}
	else {printf("não encontrou var4 - Como esperado\n");}
	
	printf("Fechando tabela ...\n");
	closeTable();

}


/**
	Testa se pilha de tabelas está funcionando adequadamente
*/
void multiTableTest(){
	printf("\n\nTESTE DA PILHA DE TABELAS\n");

	printf("Inicializando tabela global...\n");
	initTable();
	
	 
	temp = createLexval(1, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, FALSE, 0);
	printf("Inseriu \"int var1;\"\n");
	free(temp);
	temp = NULL;
	
	temp = createLexval(12, IDS, NONE, "var3", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING, NULL, 0, FALSE, 0);
	printf("Inseriu \"string var3;\"\n");
	free(temp);
	temp = NULL;

	printf("Inicializando tabela local...\n");
	initTable();
	
	temp = createLexval(17, IDS, NONE, "var2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT, NULL, 0, FALSE, 0);
	printf("Inseriu \"float var2;\"\n");
	free(temp);
	temp = NULL;

	//símbolo deve ocultar o símbolo var1 global	
	temp = createLexval(21, IDS, NONE, "var1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, STRING, NULL, 0, FALSE, 0);
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

/**
	Testa vetores na tabela de símbolos
*/
void vecTableTest(){

	printf("\n\nTESTE DE VETORES NA TABELA\n");

	printf("Inicializando tabela ...\n");	
	initTable();

	temp = createLexval(21, IDS, NONE, "vec1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 12, FALSE, 0);
	printf("Inseriu \"vec1[12] int;\"\n");
	free(temp);
	temp = NULL;

	temp = createLexval(21, IDS, NONE, "vec2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT, NULL, 1000, FALSE, 0);
	printf("Inseriu \"vec2[1000] float;\"\n");
	free(temp);
	temp = NULL;

	temp = createLexval(21, IDS, NONE, "vec3", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, CHAR, NULL, 3, FALSE, 0);
	printf("Inseriu \"vec3[3] char;\"\n");
	free(temp);
	temp = NULL;

	Hash* vec1 = getSymbol("vec1");
	if(vec1 != NULL){
		printf("Encontrou vec1\n");
		printf("vec1 tem tamanho = %d contendo %d elementos\n", vec1->size, vec1->vecSize);
	}else{
		printf("Não encontrou vec1\n");
	}

	Hash* vec2 = getSymbol("vec2");
	if(vec2 != NULL){
		printf("Encontrou vec2\n");
		printf("vec2 tem tamanho = %d contendo %d elementos\n", vec2->size, vec2->vecSize);
	}else{
		printf("Não encontrou vec2\n");
	}

	Hash* vec3 = getSymbol("vec3");
	if(vec3 != NULL){
		printf("Encontrou vec3\n");
		printf("vec3 tem tamanho = %d contendo %d elementos\n", vec3->size, vec3->vecSize);
	}else{
		printf("Não encontrou vec3\n");
	}	
	printf("Fechando tabela...\n");
	closeTable();
}

/**
	Testa tipos de usuário na tabela de símbolos
*/
void userTypeTableTest(){
	printf("\n\nTESTE DE TIPOS DE USUÁRIO NA TABELA\n");
	printf("Inicializando tabela ...\n");
	initTable();
	
	temp = createLexval(21, IDS, NONE, "ut1", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, USER, NULL, 0, FALSE, 0);
	addField("ut1", createUserTypeField(PROTECTED_ENCAPS, FLOAT, "f"));
	addField("ut1", createUserTypeField(PUBLIC_ENCAPS, INT, "tel"));
	
	printf("Inseriu \"class ut1 [protected float f : int tel];\"\n");	
	free(temp);
	temp = NULL;	

	Hash* ut1 = getSymbol("ut1");
	if(ut1 !=NULL){
		printf("Encontrou ut1\n");
		printf("ut1 tem %d campos, seu tamanho é %d\n", ut1->fieldsNum, ut1->size);
		int i;
		printf("ut1 tem os seguintes campos:\n");		
		for(i = 0; i<ut1->fieldsNum; i++){
			switch(ut1->fields[i]->fieldEncaps){
				case PUBLIC_ENCAPS: printf("\tpublic "); break;
				case PROTECTED_ENCAPS: printf("\tprotected "); break;
				case PRIVATE_ENCAPS: printf("\tprivate "); break;
			}
			switch(ut1->fields[i]->fieldType){
				case CHAR: printf("char "); break;
				case STRING: printf("string "); break; 
				case INT: printf("int "); break;
				case FLOAT: printf("float "); break;
				case BOOL: printf("bool "); break;
			}
			printf("%s\n", ut1->fields[i]->fieldName);
		}
	}
	else{
		printf("Não encontrou ut1\n");
	}
	printf("Fechando tabela ...\n");
	closeTable();
}

/**
	Testa funções na tabela de símbolos
*/
void funTableTest(){
	printf("\n\nTESTE DE FUNÇÕES NA TABELA\n");

	printf("Inicializando tabela ...\n");
	initTable();	
	
	temp = createLexval(16, IDS, NONE, "foo", TRUE);	
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, TRUE, 0);
	addFuncArg("foo", createFuncArg(INT, NULL, "a", FALSE));
	addFuncArg("foo", createFuncArg(FLOAT, NULL, "b", TRUE));
	addFuncArg("foo", createFuncArg(USER, "tipoDoWill", "tdw", TRUE));
	printf("Inseriu \"int foo(int a, const float b, const tipoDoWill tdw);\"\n");
	free(temp);
	temp = NULL;

	Hash* foo = getSymbol("foo");
	if(foo !=NULL){
		printf("Encontrou foo\n");
		printf("foo tem %d argumentos\n", foo->argsNum);
		int i;
		printf("foo tem os seguintes argumentos:\n");		
		for(i = 0; i<foo->argsNum; i++){
			if (foo->args[i]->isConst) printf("const ");
			switch(foo->args[i]->argType){
				case CHAR: printf("char "); break;
				case STRING: printf("string "); break; 
				case INT: printf("int "); break;
				case FLOAT: printf("float "); break;
				case BOOL: printf("bool "); break;
				case USER: printf("%s ", foo->args[i]->userType);
			}
			printf("%s\n", foo->args[i]->argName);
		}
	}
	else{
		printf("Não encontrou ut1\n");
	}

	printf("Fechando tabela ...\n");
	closeTable();
	
}

void errorsTest(){
	printf("\n\nTESTE DE ERROS NA TABELA\n");
	printf("Inicializando tabela ...\n");
	initTable();
	printf("Testando erro de dupla declaração -> 101:\n");
	temp = createLexval(21, IDS, NONE, "var1", TRUE);
	if(!addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, FALSE, 0)){
		printf("Inseriu \"int var1;\"\n");
	}
	free(temp);
	temp = NULL;

	temp = createLexval(27, IDS, NONE, "var1", TRUE);
	if(!addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT, NULL, 0, TRUE, 0)){
		printf("Inseriu \"float var1();\"\n");
	}
	else{
		printf("Não conseguiu inserir float var1(); ERRO = %d\n", addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT, NULL, 0, TRUE, 0));
	} 
	free(temp);

	temp = createLexval(16, IDS, NONE, "foo", TRUE);	
	addSymbol(temp, NATUREZA_IDENTIFICADOR, INT, NULL, 0, TRUE, 0);
	addFuncArg("foo", createFuncArg(INT, NULL, "a", FALSE));
	addFuncArg("foo", createFuncArg(FLOAT, NULL, "b", TRUE));
	addFuncArg("foo", createFuncArg(USER, "tipoDoWill", "tdw", TRUE));
	free(temp);
	
	temp = createLexval(21, IDS, NONE, "vec2", TRUE);
	addSymbol(temp, NATUREZA_IDENTIFICADOR, FLOAT, NULL, 1000, FALSE, 0);
	free(temp);
	temp = NULL;

	printf("Testando erro de símbolo não declarado -> 100:\n");
	if(isDefined("undeclared")){
		printf("Não encontrou símbolo \"undeclared\"; Erro = %d\n", isDefined("undeclared"));
	}
	printf("Testando erro de símbolo não ser usado como variável -> 200:\n");
	if(isVariable("foo")!=TRUE){
		printf("Símbolo \"foo\" não é uma variável; Erro = %d\n", isVariable("foo"));	
	}
	if(isVariable("vec2")!=TRUE){
		printf("Símbolo \"vec2\" não é uma variável; Erro = %d\n", isVariable("vec2"));	
	}
	if(isVariable("var1") == TRUE){
		printf("Símbolo \"var1\" é variável\n");
	}

	printf("Testando erro de símbolo não ser usado como vetor -> 201:\n");
	if(isVector("foo")!=TRUE){
		printf("Símbolo \"foo\" não é um vetor; Erro = %d\n", isVector("foo"));	
	}
	if(isVector("vec2")==TRUE){
		printf("Símbolo \"vec2\" é um vetor\n");	
	}
	if(isVector("var1") != TRUE){
		printf("Símbolo \"var1\" não é um vetor; Erro = %d\n", isVector("var1"));
	}
	
	printf("Testando erro de símbolo não ser usado como função -> 202:\n");
	if(isFunction("foo")==TRUE){
		printf("Símbolo \"foo\" é uma função\n");	
	}
	if(isFunction("vec2")!=TRUE){
		printf("Símbolo \"vec2\" não é uma função; Erro = %d\n", isFunction("vec2"));	
	}
	if(isFunction("var1") != TRUE){
		printf("Símbolo \"var1\" não é uma função; Erro = %d\n", isFunction("var1"));
	}
	
	printf("Fechando tabela ...\n");
	closeTable();
	
}
int main(){
	oneTableTest();
	multiTableTest();
	vecTableTest();
	userTypeTableTest();
	funTableTest();
	errorsTest();
}

