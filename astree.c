//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astree.h"


ASTREE *astreeCreate(int type, HASH_NODE *symbol, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3) 
{
	ASTREE *newNode = 0;
	newNode = (ASTREE*) calloc(1,sizeof(ASTREE));

	newNode->type   = type;
	newNode->symbol = symbol;	

	newNode->son[0] = son0;
	newNode->son[1] = son1;
	newNode->son[2] = son2;
	newNode->son[3] = son3;

	return newNode;
}


void astreePrint(ASTREE *node, int level)
{
	int i;

	if(node) 
	{
		for(i=0; i<level; i++)
			fprintf(stderr, " ");

		fprintf(stderr, "ASTREE( ");

		switch(node->type)
		{
			case ASTREE_SYMBOL :	 		fprintf(stderr, "ASTREE_SYMBOL"); break;			
			case ASTREE_CMD_ATRIBUICAO : 	fprintf(stderr, "ASTREE_CMD_ATRIBUICAO"); break;
			case ASTREE_CMD_IF : 			fprintf(stderr, "ASTREE_CMD_IF"); break;
			case ASTREE_CMD_IF_ELSE : 		fprintf(stderr, "ASTREE_CMD_IF_ELSE"); break;
			case ASTREE_CMD_FOR : 			fprintf(stderr, "ASTREE_CMD_FOR"); break;
			case ASTREE_CMD_FOR_TO : 		fprintf(stderr, "ASTREE_CMD_FOR_TO"); break;
			case ASTREE_CMD_READ : 			fprintf(stderr, "ASTREE_CMD_READ"); break;
			case ASTREE_CMD_PRINT : 		fprintf(stderr, "ASTREE_CMD_PRINT"); break;
			case ASTREE_CMD_RETURN : 		fprintf(stderr, "ASTREE_CMD_RETURN"); break;
			case ASTREE_VETOR : 			fprintf(stderr, "ASTREE_VETOR"); break;
			case ASTREE_CHAMADA_FUNCAO : 	fprintf(stderr, "ASTREE_CHAMADA_FUNCAO"); break;
			case ASTREE_EXP_PARENTESES: 	fprintf(stderr, "ASTREE_EXP_PARENTESES"); break;
			case ASTREE_NEGACAO : 			fprintf(stderr, "ASTREE_NEGACAO"); break;
			case ASTREE_ADD : 				fprintf(stderr, "ASTREE_ADD"); break;
			case ASTREE_SUB : 				fprintf(stderr, "ASTREE_SUB"); break;
			case ASTREE_MUL : 				fprintf(stderr, "ASTREE_MUL"); break;
			case ASTREE_DIV : 				fprintf(stderr, "ASTREE_DIV"); break;
			case ASTREE_MENOR : 			fprintf(stderr, "ASTREE_MENOR"); break;
			case ASTREE_MAIOR : 			fprintf(stderr, "ASTREE_MAIOR"); break;
			case ASTREE_LE : 				fprintf(stderr, "ASTREE_LE"); break;
			case ASTREE_GE : 				fprintf(stderr, "ASTREE_GE"); break;
			case ASTREE_EQ : 				fprintf(stderr, "ASTREE_EQ"); break;
			case ASTREE_NE : 				fprintf(stderr, "ASTREE_NE"); break;
			case ASTREE_AND : 				fprintf(stderr, "ASTREE_AND"); break;
			case ASTREE_OR : 				fprintf(stderr, "ASTREE_OR"); break;
			case ASTREE_ARGUMENTOS : 		fprintf(stderr, "ASTREE_ARGUMENTOS"); break;
			case ASTREE_RESTO_ARGUMENTOS : 	fprintf(stderr, "ASTREE_RESTO_ARGUMENTOS"); break;
			case ASTREE_LISTA_COMANDOS :	fprintf(stderr, "ASTREE_LISTA_COMANDOS"); break;
			case ASTREE_COMANDOS :			fprintf(stderr, "ASTREE_COMANDOS"); break;
			case ASTREE_LISTA_DECLARACOES :	fprintf(stderr, "ASTREE_LISTA_DECLARACOES"); break;
			case ASTREE_DECLARACOES :		fprintf(stderr, "ASTREE_DECLARACOES"); break;
			case ASTREE_VARIAVEL :		fprintf(stderr, "ASTREE_VARIAVEL"); break;
			case ASTREE_VETOR_DECLARADO :		fprintf(stderr, "ASTREE_VETOR_DECLARADO"); break;
case ASTREE_INT :		fprintf(stderr, "ASTREE_INT"); break;
case ASTREE_FLOAT :		fprintf(stderr, "ASTREE_FLOAT"); break;
case ASTREE_BOOL :		fprintf(stderr, "ASTREE_BOOL"); break;
case ASTREE_CHAR :		fprintf(stderr, "ASTREE_CHAR"); break;
			default: 						fprintf(stderr, "ASTREE_UNKNOWN"); break;
		}
		
		fprintf(stderr,",");
		

		if(node->symbol)
			fprintf(stderr, "%s \n", node->symbol->text);
		else
			fprintf(stderr,"\n");

	
		// chamada recursivamente para os filhos
		for(i=0; i<MAX_SONS; i++)
			astreePrint(node->son[i],level+1);		
	
	
	}

}


