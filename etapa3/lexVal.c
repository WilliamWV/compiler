//Passando um void como valor para poder determinar qual campo do union que deve ser assinalado
//por meio do tipo presente em literType
struct lexval* createLexVal(int line, int tkType, int ltType, void* val){
	struct lexval* temp = (struct lexval*) malloc(sizeof(struct lexval));
	temp->lineNumber = line;
	temp->tokenType = tkType;
	temp->literType = ltType;
	switch (ltType){
		case INT: temp->value.i = *( (int*) val ); break;
		case FLOAT: temp->value.f = *( (float*) val); break;
		case CHAR: temp->value.c = *( (char*) val); break;
		case BOOL: temp->value.b = *( (bool*) val); break;
		case STRING:
		case NONE: temp->value.str = strdup( (char*) val);  	
	}
	return temp;
}
