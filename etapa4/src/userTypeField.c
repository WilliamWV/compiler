#include "../include/userTypeField.h"
#include "../include/tree.h"
#include <stdio.h>

Fields *currentFields = NULL;
int camposNoTipoAtual = 0;

Fields *criaCampo(Node *field){
	Fields *newField = malloc(sizeof(Fields));
	newField->field = malloc(sizeof(UserTypeField));
	int i = 0;
	if(field!=NULL){
		adicionaInfoACampo(field, newField);
		while(i < field->kidsNumber){
			
			adicionaInfoACampo(field->kids[i], newField);
			i++;
		}
	}
	camposNoTipoAtual++;
	newField->next = NULL;

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
					}
					else if(strcmp(string, "float") == 0){
						newField->field->fieldType = FLOAT;			
					}
					else if(strcmp(string, "bool") == 0){
						newField->field->fieldType = BOOL;			
					}
					else if(strcmp(string, "char") == 0){
						newField->field->fieldType = CHAR;
					}
					else if(strcmp(string, "string") == 0){
						newField->field->fieldType = STRING;		
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
			//adicionaInfoACampo(field->kids[i], newField);
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

	while(camposNoTipoAtual > 0){
		aux = currentFields;
		int i = 0;
		while(i < camposNoTipoAtual - 1){
			aux = aux->next;
			i++;
		}
		if(aux->next != NULL)
			free(aux->next);
		free(aux);
		camposNoTipoAtual--;
	}
	currentFields = NULL;
}
