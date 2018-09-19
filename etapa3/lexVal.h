//Definição de bool baseado em int para funcionar em versões mais antigas do C
typedef int bool;


union Value{
	int i;
	float f;
	char c;
	bool b;
	char* str; 
};

struct lexval{
	int lineNumber; 
	int tokenType; 
	int literType;
	union Value value; //um dos campos da union acima
};
