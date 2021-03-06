%{

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "hash.h"
#include "y.tab.h"


extern HASH_NODE *Table[HASH_SIZE];

int running = 1;
int linecounter = 1;

int getLineNumber(void);
int isRunning(void);



%}

	
%x IN_COMMENT

%%
<<EOF>>				{ running = 0; return 0;}		
[\t ]				{ ; }
"//".*\n 			{ linecounter++; }
\n				{ linecounter++; }


<INITIAL>{
     "/*"      BEGIN(IN_COMMENT);
     }
<IN_COMMENT>{
     "*/"      BEGIN(INITIAL);
     [^*\n]+   
     "*"       
     \n        linecounter++; printf("Line: %d\n", linecounter);
     }




"int"				{ return KW_INT; 		}
"float"				{ return KW_FLOAT; 		}
"bool"				{ return KW_BOOL; 		}
"char"				{ return KW_CHAR; 		}
"if"				{ return KW_IF; 		}
"then"              		{ return KW_THEN; 		}
"else"				{ return KW_ELSE; 		}
"for"				{ return KW_FOR; 		}
"to"				{ return KW_TO; 		}
"read"				{ return KW_READ; 		}
"print"				{ return KW_PRINT; 		}
"return"			{ return KW_RETURN; 		}

"<="				{ return OPERATOR_LE; 	}
">="				{ return OPERATOR_GE; 	}
"=="				{ return OPERATOR_EQ; 	}
"!="				{ return OPERATOR_NE; 	}
"&&"				{ return OPERATOR_AND; 	}
"||"				{ return OPERATOR_OR; 	}

[-,;:(){}\[\]+*/<>!&$=] 	{ return yytext[0]; }



"TRUE"							{ yylval.symbol=(hashInsert(LIT_TRUE, yytext));  return LIT_TRUE;	}
"FALSE"							{ yylval.symbol=(hashInsert(LIT_FALSE, yytext)); return LIT_FALSE;			}
[a-zA-Z][a-zA-Z0-9_]*					{ yylval.symbol=(hashInsert(TK_IDENTIFIER, yytext)); return TK_IDENTIFIER;	 	}
[0-9]+							{ yylval.symbol=(hashInsert(LIT_INTEGER, yytext)); return LIT_INTEGER; 			}
\'([^\\\"]|\\.)\'				{ yylval.symbol=(hashInsert(LIT_CHAR, yytext)); return LIT_CHAR; 			}
\"([^\\\"]|\\.)*\"				{ yylval.symbol=(hashInsert(LIT_STRING, yytext)); return LIT_STRING; 			}

.        					{ return TOKEN_ERROR;}
	


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

void initMe(void) {
}

