//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include "lex.yy.h"
#include "y.tab.h"
#include "astree.h"

FILE *fileout;

int main(int argc, char *argv[])
{
	
	// para debugar o yacc
	int yydebug=1; 
	
	initHash();
	
	// valida se foi passado o arquivo de entrada como parâmetro
	if(argc < 3){
		fprintf(stderr,"\nError: Call input filename.\n");
		exit(1);
	}

	extern FILE* yyin;
	yyin=fopen(argv[1],"r");
	
	// validação do arquivo de entrada => arquivo fonte de um programa
	if(!yyin) {
		printf("\nError: Can not open the 'input program file'.\n");
		exit(2);
	}
	
	//abre arquivo de saída para escrita
	fileout=fopen(argv[2], "w+");
	
	// validação do arquivo de saída
	if(!fileout) {
		printf("\nError: Can not open the 'output file'.\n");
		exit(2);
	}	
	
	yyparse();
	//hashPrint();

	// se der sucesso, retorna 0 como saída //
	exit(0);


}



