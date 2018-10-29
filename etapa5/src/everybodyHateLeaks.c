#include "../include/everybodyHateLeaks.h"
struct ptrs* pointers = NULL;

void addPointer(void* p){
	struct ptrs* aux = pointers;
	if(pointers == NULL){
		pointers = (struct ptrs*) malloc(sizeof(struct ptrs));
		pointers->ptr = p;
		pointers->next = NULL;
	}
	else{
	
		while(aux->next!=NULL){
			aux = aux->next;
		}
		aux->next= (struct ptrs*) malloc(sizeof(struct ptrs));
		aux->next->ptr = p;
		aux->next->next = NULL;
	}
}

void* aloca(size_t s)
{
	void* p = malloc(s);	
	addPointer(p);
	return p;
}


void liberaTudo()
{
	struct ptrs* aux;
	while(pointers!=NULL){
		aux = pointers;
		free(pointers->ptr);
		pointers = pointers->next;
		free(aux);
	}
}
