#include "tree.h"
#include "hash.h"

//Definição dos modificadores de encapsulamento
#define PUBLIC_ENCAPS     0x10
#define PRIVATE_ENCAPS    0x11
#define PROTECTED_ENCAPS  0X12

typedef struct fieldList{
	UserTypeField *field;
	struct fieldList *next;
} Fields;

void adicionaCampo(Fields *newField);

Fields *criaCampo(Node *field);

void addFieldsToSymbol(char* symbol, Fields *fields);

void adicionaInfoACampo(Node* field, Fields *newField);

void clearCurrentFields();
