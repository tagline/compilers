//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

%{

#include <stdio.h>
#include <stdlib.h>
#include "astree.c"

#define   SYMBOL_UNDEFINED		0 
#define   SYMBOL_TK_IDENTIFIER  	1 
#define   SYMBOL_LIT_INTEGER  		2 
#define   SYMBOL_LIT_TRUE   		3 
#define   SYMBOL_LIT_FALSE  		4	 
#define   SYMBOL_LIT_CHAR   		5 
#define   SYMBOL_LIT_STRING  		6 

%}

%type <astree>bloco;
%type <astree>comandos;
%type <astree>lista_de_comandos;
%type <astree>expressao;
%type <astree>argumentos;
%type <astree>resto_argumentos;



%union {
	struct hash_node* symbol;
	struct astree_node* astree;
} 


/* 		Tokens
 * -----------------
 */

%token KW_INT        		
%token KW_FLOAT      		
%token KW_BOOL       		
%token KW_CHAR       		
%token KW_IF         		
%token KW_THEN       		
%token KW_ELSE       		
%token KW_FOR        		
%token KW_READ       		
%token KW_RETURN     		
%token KW_PRINT      		
%token KW_TO         		

%token OPERATOR_LE   		
%token OPERATOR_GE   		
%token OPERATOR_EQ   		
%token OPERATOR_NE   		
%token OPERATOR_AND  		
%token OPERATOR_OR   		

%token <symbol>TK_IDENTIFIER		
%token <symbol>LIT_INTEGER		
%token <symbol>LIT_TRUE		
%token <symbol>LIT_FALSE		
%token <symbol>LIT_CHAR		
%token <symbol>LIT_STRING		

%token <symbol>TOKEN_ERROR			


/* 		Precedência 
 * ------------------------
 */

%left '+' '-'
%left '*' '/' 
%left OPERATOR_AND OPERATOR_OR
%left '<' '>' OPERATOR_LE OPERATOR_GE OPERATOR_EQ OPERATOR_NE
%right '!'
%nonassoc KW_ELSE

%%

programa : lista_declaracoes
	 ;
		
lista_declaracoes : lista_declaracoes declaracoes
	 	  | declaracoes
	          ;

declaracoes : declaracao_vars_globais ';'
	    | declaracao_vetores ';'
	    | declaracao_funcao ';'
	    ;

declaracao_vars_globais : tipo TK_IDENTIFIER ':' literais
		        ;

declaracao_vetores : 	tipo TK_IDENTIFIER '[' LIT_INTEGER ']'
			| tipo TK_IDENTIFIER '[' LIT_INTEGER ']' ':' ARRAYNUM
		   ;

ARRAYNUM : ARRAYNUM literais 
	 | literais
	 ;

literais : LIT_INTEGER
	 | LIT_CHAR
	 | LIT_STRING 
	 | LIT_TRUE
	 | LIT_FALSE
	 ;

declaracao_funcao : tipo TK_IDENTIFIER '(' parametros_chamada ')' bloco   
 	     	  ;

parametros_chamada : tipo TK_IDENTIFIER parametros_resto	 	
		   |
		   ;

parametros_resto : ',' tipo TK_IDENTIFIER parametros_resto
		 |
		 ;


tipo : KW_INT
     | KW_FLOAT
     | KW_BOOL
     | KW_CHAR
     ;

bloco : '{' lista_de_comandos '}' 				 	 { astreePrint($1,0); }
      ;

// pode ter 1 comando ou uma lista
lista_de_comandos : lista_de_comandos comandos ';'			{ $$ = astreeCreate(ASTREE_CMD_ATRIBUICAO,0,$1,$2,0,0);	}
	 	  | comandos ';' 					{ $$ = astreeCreate(ASTREE_CMD_ATRIBUICAO,0,$1,0,0,0);	}
		  ;
	
comandos : TK_IDENTIFIER '=' expressao  				{ $$ = astreeCreate(ASTREE_CMD_ATRIBUICAO,$1,$3,0,0,0);	}
	 | TK_IDENTIFIER '[' expressao ']' '=' expressao   		{ $$ = astreeCreate(ASTREE_CMD_FOR,$1,$3,$6,0,0);	}
	 | KW_IF '(' expressao ')' KW_THEN comandos 			{ $$ = astreeCreate(ASTREE_CMD_IF,0,$3,$6,0,0);	}
	 | KW_IF '(' expressao ')' KW_THEN comandos KW_ELSE comandos	{ $$ = astreeCreate(ASTREE_CMD_IF_ELSE,0,$3,$6,$8,0);	}
	 | KW_FOR '(' expressao ')' comandos 				{ $$ = astreeCreate(ASTREE_CMD_FOR,0,$3,$5,0,0);	}
	 | KW_FOR '(' TK_IDENTIFIER '=' expressao KW_TO expressao ')' comandos  { $$ = astreeCreate(ASTREE_CMD_FOR_TO,$3,$5,$7,$9,0); }	
	 | KW_PRINT print  						{ $$ = 0; }	
	 | KW_READ TK_IDENTIFIER 					{ $$ = 0; }
	 | KW_RETURN expressao						{ $$ = 0; }    
	 | bloco							{ $$ = astreeCreate(ASTREE_CMD_FOR,0,$1,0,0,0);}
	 | 								{ $$ = 0; }
	 ;

print : LIT_STRING print						 // como fazer aqui?!
      | expressao print							 
      | LIT_STRING							 
      | expressao 							 
      ;

expressao : TK_IDENTIFIER						 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_INTEGER							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_TRUE							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_FALSE							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_CHAR							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| TK_IDENTIFIER '[' expressao ']'				 { $$ = astreeCreate(ASTREE_VETOR,$1,$3,0,0,0);		}
	| TK_IDENTIFIER '(' argumentos ')'				 { $$ = astreeCreate(ASTREE_CHAMADA_FUNCAO,$1,0,$3,0,0);}
	| '(' expressao ')'					         { $$ = astreeCreate(ASTREE_EXP_PARENTESES,0,$2,0,0,0); }
	| '!' expressao							 { $$ = astreeCreate(ASTREE_NEGACAO,0,$2,0,0,0);	}
	| expressao '+' expressao					 { $$ = astreeCreate(ASTREE_ADD,0,$1,$3,0,0);		}
	| expressao '-' expressao					 { $$ = astreeCreate(ASTREE_SUB,0,$1,$3,0,0);		}
	| expressao '*' expressao					 { $$ = astreeCreate(ASTREE_MUL,0,$1,$3,0,0);		}
	| expressao '/' expressao					 { $$ = astreeCreate(ASTREE_DIV,0,$1,$3,0,0);		}
	| expressao '<' expressao					 { $$ = astreeCreate(ASTREE_MENOR,0,$1,$3,0,0);		}
	| expressao '>' expressao					 { $$ = astreeCreate(ASTREE_MAIOR,0,$1,$3,0,0);		}
	| expressao OPERATOR_LE expressao				 { $$ = astreeCreate(ASTREE_LE,0,$1,$3,0,0);		}
	| expressao OPERATOR_GE expressao				 { $$ = astreeCreate(ASTREE_GE,0,$1,$3,0,0);		}
	| expressao OPERATOR_EQ expressao				 { $$ = astreeCreate(ASTREE_EQ,0,$1,$3,0,0);		}
	| expressao OPERATOR_NE expressao				 { $$ = astreeCreate(ASTREE_NE,0,$1,$3,0,0);		}
	| expressao OPERATOR_AND expressao				 { $$ = astreeCreate(ASTREE_AND,0,$1,$3,0,0);		}
	| expressao OPERATOR_OR expressao				 { $$ = astreeCreate(ASTREE_OR,0,$1,$3,0,0);		}
	;

argumentos :  expressao resto_argumentos			 	 { $$ = astreeCreate(ASTREE_ARGUMENTOS,0,$1,$2,0,0);	}
	   |								 { $$ = 0;}
           ; 

resto_argumentos : ','  expressao resto_argumentos			 { $$ = astreeCreate(ASTREE_RESTO_ARGUMENTOS,0,$2,$3,0,0);}
     		 |							 { $$ = 0;}
      		 ;


%%


int yyerror ()
{
	printf ("Sintax Error: in line number %d\n", getLineNumber());
	exit(3);
}