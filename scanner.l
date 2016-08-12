//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

%{
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "tokens.h"
#include "hash.h"

extern HASH_NODE *Table[HASH_SIZE];

int running = 1;
int linecounter = 0;

// não sei se isso vai aqui ou na main ???!!!!
int getLineNumber(void);
int isRunning(void);


%}

%x COMMENT


%%


"int"				{ printf("INT\n\n"); 	return TOKEN_INT; 	}
"float"				{ printf("FLOAT\n\n"); 	return TOKEN_FLOAT; 	}
"bool"				{ printf("BOOL\n\n"); 	return TOKEN_BOOL; 	}
"char"				{ printf("CHAR\n\n"); 	return TOKEN_CHAR; 	}
"if"				{ printf("IF\n\n"); 	return TOKEN_IF; 	}
"then"                  	{ printf("THEN\n\n"); 	return TOKEN_THEN; 	}
"else"				{ printf("ELSE\n\n"); 	return TOKEN_ELSE; 	}
"for"				{ printf("FOR\n\n"); 	return TOKEN_FOR; 	}
"read"				{ printf("READ\n\n"); 	return TOKEN_READ; 	}
"print"				{ printf("PRINT\n\n"); 	return TOKEN_PRINT; 	}
"return"			{ printf("RETURN\n\n"); return TOKEN_RETURN; 	}

[,;:\(\)\[\]\{\}+-*/<>!&$ ]     { printf("CARACTER ESPECIAL '%c'\n\n", yytext[0]); return yytext[0];}


"<="				{ printf("<=\n\n"); 	return OPERATOR_LE; 	}
">="				{ printf(">=\n\n"); 	return OPERATOR_GE; 	}
"=="				{ printf("==\n\n"); 	return OPERATOR_EQ; 	}
"!="				{ printf("!=\n\n"); 	return OPERATOR_NE; 	}
"&&"				{ printf("&&\n\n"); 	return OPERATOR_AND; 	}
"||"				{ printf("||\n\n"); 	return OPERATOR_OR; 	}







%%



int getLineNumber(void)
{
	return linecounter;
}

int isRunning(void)
{
	return running;
}

int yywrap(void)
{
	running = 0;
	return 1;
}


