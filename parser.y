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

%type <astree>programa; 
%type <astree>bloco;
%type <astree>comandos;
%type <astree>lista_de_comandos;
%type <astree>expressao;
%type <astree>argumentos;
%type <astree>resto_argumentos;
%type <astree>lista_declaracoes 
%type <astree>declaracoes
%type <astree>declaracao_vars_globais
%type <astree>declaracao_funcao
%type <astree>declaracao_vetores
%type <astree>tipo
%type <astree>literais
%type <astree>ARRAYNUM
%type <astree>parametros_chamada
%type <astree>parametros_resto
%type <astree>print


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

programa : lista_declaracoes						{ $$ = astreeCreate(ASTREE_PROGRAMA, 0, $1, 0, 0, 0); 
									  astreePrint($$,0);
									  astreeDecompile($1,ASTREE_PROGRAMA);
									}
	 ;
		
lista_declaracoes : lista_declaracoes declaracoes 			{ $$ = astreeCreate(ASTREE_LISTA_DECLARACOES,0,$1,$2,0,0); }
	 	  | declaracoes						{ $$ = astreeCreate(ASTREE_LISTA_DECLARACOES,0,$1,0,0,0); }
	          ;

declaracoes : declaracao_vars_globais ';'				{ $$ = astreeCreate(ASTREE_DECLARACOES,0,$1,0,0,0); }
	    | declaracao_vetores ';'					{ $$ = astreeCreate(ASTREE_DECLARACOES,0,$1,0,0,0); }
	    | declaracao_funcao ';'					{ $$ = astreeCreate(ASTREE_DECLARACOES,0,$1,0,0,0); }
	    ;

declaracao_vars_globais : tipo TK_IDENTIFIER ':' literais		{ $$ = astreeCreate(ASTREE_VARIAVEL,$2,$1,$4,0,0); }
		        ;


declaracao_vetores : 	tipo TK_IDENTIFIER '[' LIT_INTEGER ']'		{ $$ = astreeCreate(ASTREE_VETOR,$2,$1,astreeCreate(ASTREE_SYMBOL,$4,0,0,0,0),0,0);	}
		| tipo TK_IDENTIFIER '[' LIT_INTEGER ']' ':' ARRAYNUM	{ $$ = astreeCreate(ASTREE_VETOR_DECLARADO ,$2,$1,astreeCreate(ASTREE_SYMBOL,$4,0,0,0,0),$7,0);	}
		;

ARRAYNUM : ARRAYNUM literais						{ $$ = astreeCreate(ASTREE_VETOR_CONTEUDO,0,$2,$1,0,0);	}
	 | literais							{ $$ = astreeCreate(ASTREE_VETOR_CONTEUDO,0,$1,0,0,0);	}
	 ;

literais : LIT_INTEGER							{ $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);	}
	 | LIT_CHAR							{ $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);	}
	 | LIT_STRING 							{ $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);	}
	 | LIT_TRUE							{ $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);	}
	 | LIT_FALSE							{ $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);	}
	 ;

declaracao_funcao : tipo TK_IDENTIFIER '(' parametros_chamada ')' bloco  { $$ = astreeCreate(ASTREE_DECLARACAO_FUNCAO,$2,$1,$4,$6,0);	}  
 	     	  ;

parametros_chamada : tipo TK_IDENTIFIER parametros_resto		{ $$ = astreeCreate(ASTREE_PARAMETROS,$2,$1,$3,0,0);	} 	
		   |							{ $$ = 0; } //astreeCreate(ASTREE_VAZIO,0,0,0,0,0); 		}
		   ;

parametros_resto : ',' tipo TK_IDENTIFIER parametros_resto		{ $$ = astreeCreate(ASTREE_PARAMETROS_RESTO,$3,$2,$4,0,0);	}
	 	 |							{ $$ = 0; } //astreeCreate(ASTREE_VAZIO,0,0,0,0,0); 		}
		 ;


tipo : KW_INT								{ $$ = astreeCreate(ASTREE_INT,0,0,0,0,0);	}
     | KW_FLOAT								{ $$ = astreeCreate(ASTREE_FLOAT,0,0,0,0,0);	}
     | KW_BOOL								{ $$ = astreeCreate(ASTREE_BOOL,0,0,0,0,0);	}
     | KW_CHAR								{ $$ = astreeCreate(ASTREE_CHAR,0,0,0,0,0);	}
     ;

bloco : '{' lista_de_comandos '}' 					{ $$ = astreeCreate(ASTREE_BLOCO,0,$2,0,0,0);	}
      ;

// pode ter 1 comando ou uma lista
lista_de_comandos : lista_de_comandos comandos ';'			{ $$ = astreeCreate(ASTREE_LISTA_COMANDOS,0,$1,$2,0,0);	}
	 	  | comandos ';' 		        		{ $$ = astreeCreate(ASTREE_LISTA_COMANDOS,0,$1,0,0,0);  }	
		  ;
	
comandos : TK_IDENTIFIER '=' expressao  				{ $$ = astreeCreate(ASTREE_CMD_ATRIBUICAO,$1,$3,0,0,0);	}
	 | TK_IDENTIFIER '[' expressao ']' '=' expressao		{ $$ = astreeCreate(ASTREE_CMD_ATRIBUICAO_VETOR,$1,$3,$6,0,0);	}
	 | KW_IF '(' expressao ')' KW_THEN comandos 			{ $$ = astreeCreate(ASTREE_CMD_IF,0,$3,$6,0,0);	}
	 | KW_IF '(' expressao ')' KW_THEN comandos KW_ELSE comandos	{ $$ = astreeCreate(ASTREE_CMD_IF_ELSE,0,$3,$6,$8,0);	}
	 | KW_FOR '(' expressao ')' comandos 				{ $$ = astreeCreate(ASTREE_CMD_FOR,0,$3,$5,0,0);	}
	 | KW_FOR '(' TK_IDENTIFIER '=' expressao KW_TO expressao ')' comandos  { $$ = astreeCreate(ASTREE_CMD_FOR_TO,$3,$5,$7,$9,0); }	
	 | KW_PRINT print  						{ $$ = astreeCreate(ASTREE_CMD_PRINT,0,$2,0,0,0);	}	
	 | KW_READ TK_IDENTIFIER 					{ $$ = astreeCreate(ASTREE_CMD_READ,$2,0,0,0,0);	}
	 | KW_RETURN expressao						{ $$ = astreeCreate(ASTREE_CMD_RETURN,0,$2,0,0,0);	} 
	 | bloco							{ $$ = astreeCreate(ASTREE_VAZIO,0,$1,0,0,0);		}
	 |						                { $$ = astreeCreate(ASTREE_VAZIO,0,0,0,0,0);		}
	 ;

print : LIT_STRING print						{ $$ = astreeCreate(ASTREE_CMD_PRINT,$1,$2,0,0,0);	}
      | expressao print							{ $$ = astreeCreate(ASTREE_CMD_PRINT,0,$1,$2,0,0);	}	 
      | LIT_STRING							{ $$ = astreeCreate(ASTREE_CMD_PRINT,$1,0,0,0,0);       } 	
      | expressao 							{ $$ = astreeCreate(ASTREE_CMD_PRINT,0,$1,0,0,0);	}
      ;

expressao : TK_IDENTIFIER					 	 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_INTEGER							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_TRUE							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_FALSE							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| LIT_CHAR							 { $$ = astreeCreate(ASTREE_SYMBOL,$1,0,0,0,0);		}
	| TK_IDENTIFIER '[' expressao ']'				 { $$ = astreeCreate(ASTREE_VETOR,$1,$3,0,0,0);		}
	| TK_IDENTIFIER '(' argumentos ')'				 { $$ = astreeCreate(ASTREE_CHAMADA_FUNCAO,$1,$3,0,0,0);}
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
	   |								 { $$ = 0; }
           ; 

resto_argumentos : ','  expressao resto_argumentos			 { $$ = astreeCreate(ASTREE_RESTO_ARGUMENTOS,0,$2,$3,0,0);}
     		 |							 { $$ = 0; }
      		 ;


%%


int yyerror ()
{
	printf ("Sintax Error: in line number %d\n", getLineNumber());
	exit(3);
}
