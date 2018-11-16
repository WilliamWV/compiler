#include "tree.h"
#include "hash.h"
#include "defines.h"

typedef struct fieldList{
	UserTypeField *field;
	struct fieldList *next;
} Fields;

void adicionaCampo(Fields *newField);

Fields *criaCampo(Node *field);

void addFieldsToSymbol(char* symbol, Fields *fields);

void adicionaInfoACampo(Node* field, Fields *newField);

void clearCurrentFields();
