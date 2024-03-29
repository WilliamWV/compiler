#include "../include/userTypeField.h"
#include "../include/tree.h"
#include <stdio.h>

Fields *currentFields = NULL;
int camposNoTipoAtual = 0;
int contaCampos = 0;

Fields *criaCampo(Node *field){
	Fields *newField = malloc(sizeof(Fields));
	newField->field = malloc(sizeof(UserTypeField));
	newField->field->fieldEncaps = NOT_DEFINED_ENCAPS;
	int i = 0;
	if(field!=NULL){
		adicionaInfoACampo(field, newField);
		while(i < field->kidsNumber){
			
			adicionaInfoACampo(field->kids[i], newField);
			i++;
		}
	}
	newField->next = NULL;
	contaCampos++;
	return newField;	
}

void adicionaInfoACampo(Node* field, Fields *newField){
	int i = 0;
	if(field!=NULL){
			if(field->token != NULL){
				if(field->token->tokenType == KEYWORD){
					char *string = field->token->value.str;
					if(strcmp(string, "int") == 0){
						newField->field->fieldType = INT;
						newField->field->size = 4;					
					}
					else if(strcmp(string, "float") == 0){
						newField->field->fieldType = FLOAT;	
						newField->field->size = 8;		
					}
					else if(strcmp(string, "bool") == 0){
						newField->field->fieldType = BOOL;
						newField->field->size = 1;			
					}
					else if(strcmp(string, "char") == 0){
						newField->field->fieldType = CHAR;
						newField->field->size = 1;
					}
					else if(strcmp(string, "string") == 0){
						newField->field->fieldType = STRING;
						newField->field->size = 1;		
					}
					else if(strcmp(string, "public") == 0){
						newField->field->fieldEncaps = PUBLIC_ENCAPS;	
					}
					else if(strcmp(string, "private\0") == 0){
						newField->field->fieldEncaps = PRIVATE_ENCAPS;			
					}
					else if(strcmp(string, "protected") == 0){
						newField->field->fieldEncaps = PROTECTED_ENCAPS;				
					}
				}
				else if(field->token->tokenType == IDS){
					newField->field->fieldName = strdup(field->token->value.str);		
				}		
			}
			i++;
	}
}

void adicionaCampo(Fields *newField){
	if(currentFields == NULL) currentFields = newField;
	Fields *aux = currentFields;
	if(aux != NULL){
		while(aux->next != NULL){
			aux = aux->next;
		}
		aux->next = newField;
		newField->next = NULL;
	}	
	camposNoTipoAtual++;
}

void addFieldsToSymbol(char* symbol, Fields *fields){
	Fields *aux = fields;
	while(aux != NULL){
		if(aux->field != NULL)
			addField(symbol, aux->field);
		aux = aux->next;
	} 
}


void clearCurrentFields(){
	Fields *aux = currentFields;
	Fields *temp = aux;
	while(camposNoTipoAtual > 0){
		int contador = 0;
		aux = currentFields;
		while(aux != NULL){
			aux = aux->next;
			contador++;
		}
		aux = currentFields;
		while(contador-1 > 0){
			temp = aux;
			aux = aux->next;
			contador--;
		}		
		temp->next = NULL;
		free(aux);
		camposNoTipoAtual--;
	}
	currentFields = NULL;
}
