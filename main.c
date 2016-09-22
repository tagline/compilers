//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include "lex.yy.h"
#include "y.tab.h"


int main(int argc, char **argv)
{
	
	// para debugar o yacc
	int yydebug=1; 
	
	// valida se foi foi passado o arquivo de entrada como parâmetro
	if(argc < 2){
		fprintf(stderr,"\nError: Call input filename.\n");
	}

	extern FILE* yyin;
	yyin=fopen(argv[1],"r");
	
	// validação do arquivo de entrada
	if(!yyin) {
		printf("\nError: Can not open the file.\n");
		exit(2);
	}
	
	yyparse();
	
	//fprintf(stderr,"\n Success! \n\n");

	//hashPrint();
	
	// se der sucesso, retorna 0 como saída //
	exit(0);


}

