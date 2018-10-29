#ifndef EHL
#define EHL "ehl"

#include <stdio.h>
#include <stdlib.h>
struct ptrs{
	void* ptr;
	struct ptrs* next;
};

void* aloca(size_t s);

void liberaTudo();

#endif //EHL
