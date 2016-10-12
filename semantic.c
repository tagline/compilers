//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include "astree.h"
#include "y.tab.h"

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
