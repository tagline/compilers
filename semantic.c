//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include "astree.h"
#include "y.tab.h"


void semanticError(int line)
{
	printf ("Semantic Error: in line number %d\n", line);
	exit(4);
}

int setTypes(ASTREE *node)
{
	int i;
	
	if(!node) return -1;
	
	for(i=0; i<MAX_SONS;i++)
		setTypes(node->son[i]);
	

	if (node->type == ASTREE_VARIAVEL||
		node->type == ASTREE_PARAMETROS||
		node->type == ASTREE_PARAMETROS_RESTO
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (sonType == ASTREE_FLOAT){
			node->symbol->data_type = HASH_FLOAT;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (sonType == ASTREE_BOOL){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (sonType == ASTREE_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_SCALAR;
		}

	}

	if (node->type == ASTREE_DECLARACAO_FUNCAO
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_FUNCTION;
		}
		if (sonType == ASTREE_FLOAT){
			node->symbol->data_type = HASH_FLOAT;
			node->symbol->nature	= HASH_FUNCTION;
		}
		if (sonType == ASTREE_BOOL){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_FUNCTION;
		}
		if (sonType == ASTREE_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_FUNCTION;
		}

	}

	if (node->type ==ASTREE_VETOR_DECLARADO_1||
		node->type ==ASTREE_VETOR_DECLARADO_2
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_VECTOR;
		}
		if (sonType == ASTREE_FLOAT){
			node->symbol->data_type = HASH_FLOAT;
			node->symbol->nature	= HASH_VECTOR;
		}
		if (sonType == ASTREE_BOOL){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_VECTOR;
		}
		if (sonType == ASTREE_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_VECTOR;
		}

	}


	if (node->symbol)
	{
		if (node->symbol->type == LIT_INTEGER){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_STRING){
			node->symbol->data_type = HASH_STRING;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_FALSE){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_TRUE){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_SCALAR;
		}
	}


	return node->type;
}

int compareTypesExp(int type1,int type2)
{
	if (type1 == 0 && type2 == 0){
		return -1;
	}
	//Dois Booleanos
	if (type1 == HASH_BOOL && type2 == HASH_BOOL)
		return HASH_BOOL;
	//Pelo menos um float
	if (type1 == HASH_FLOAT)
		if (type2 == HASH_FLOAT 
			|| type2== HASH_CHAR
			|| type2 == HASH_INT)
			return HASH_FLOAT;
	if (type2 == HASH_FLOAT)
		if (type1 == HASH_FLOAT 
			|| type1 == HASH_CHAR
			|| type1 == HASH_INT)
			return HASH_FLOAT;
	//Pelo menos um int
	if (type1 == HASH_INT)
		if (type2 == HASH_CHAR
			|| type2 == HASH_INT)
			return HASH_INT;
	if (type2 == HASH_INT)
		if (type1 == HASH_CHAR
			|| type1 == HASH_INT)
			return HASH_INT;
	//Dois char
	if (type1 == HASH_CHAR && type2 == HASH_CHAR)
		return HASH_CHAR;		

	else{
		return -1;
	}
}

int compareNatures(ASTREE *node1,ASTREE *node2)
{
	if(node1->symbol->nature == node2->symbol->nature)
		return 1;
	semanticError(node1->symbol->line);
}


int checkExpression(ASTREE *node)
{
	int expType = 0;
	if (node->type == ASTREE_SYMBOL)
		return node->symbol->data_type;

	if(node->son[0]->symbol && node->son[1]->symbol){
		expType = compareTypesExp(node->son[0]->symbol->data_type,node->son[1]->symbol->data_type);
		if(expType == -1)
			semanticError(node->symbol->line);
		if(compareNatures(node->son[0],node->son[1]))
			return expType;
		else
			semanticError(node->symbol->line);
	}

	return(compareTypesExp(checkExpression(node->son[0]),checkExpression(node->son[1])));	
}


int checkSemantic(ASTREE *node)
{

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
		case ASTREE_VARIAVEL :			fprintf(stderr, "ASTREE_VARIAVEL"); break;
		case ASTREE_VETOR_DECLARADO_1 :	fprintf(stderr, "ASTREE_VETOR_DECLARADO_1"); break;
		case ASTREE_VETOR_DECLARADO_2 :	fprintf(stderr, "ASTREE_VETOR_DECLARADO_2"); break;
		case ASTREE_INT :				fprintf(stderr, "ASTREE_INT"); break;
		case ASTREE_FLOAT :				fprintf(stderr, "ASTREE_FLOAT"); break;
		case ASTREE_BOOL :				fprintf(stderr, "ASTREE_BOOL"); break;
		case ASTREE_CHAR :				fprintf(stderr, "ASTREE_CHAR"); break;
		case ASTREE_DECLARACAO_FUNCAO:	fprintf(stderr, "ASTREE_DECLARACAO_FUNCAO"); break;
		case ASTREE_BLOCO :				fprintf(stderr, "ASTREE_BLOCO"); break;
		case ASTREE_PARAMETROS:			fprintf(stderr, "ASTREE_PARAMETROS"); break;
		case ASTREE_PARAMETROS_RESTO:	fprintf(stderr, "ASTREE_PARAMETROS_RESTO"); break;			
		case ASTREE_PROGRAMA:			fprintf(stderr, "ASTREE_PROGRAMA"); break;
		case ASTREE_VETOR_CONTEUDO:		fprintf(stderr, "ASTREE_VETOR_CONTEUDO"); break;		
		default: 						fprintf(stderr, "ASTREE_UNKNOWN"); break;			
	}






}

