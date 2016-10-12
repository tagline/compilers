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
		node->type ==ASTREE_VETOR_DECLARADO_1||
		node->type ==ASTREE_VETOR_DECLARADO_2||
		node->type == ASTREE_DECLARACAO_FUNCAO||
		node->type == ASTREE_PARAMETROS||
		node->type == ASTREE_PARAMETROS_RESTO
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT)
			node->symbol->data_type = HASH_INT;
		if (sonType == ASTREE_FLOAT)
			node->symbol->data_type = HASH_FLOAT;
		if (sonType == ASTREE_BOOL)
			node->symbol->data_type = HASH_BOOL;
		if (sonType == ASTREE_CHAR)
			node->symbol->data_type = HASH_CHAR;
	}

	if (node->symbol)
	{
		if (node->symbol->type == LIT_INTEGER)
			node->symbol->data_type = HASH_INT;
		if (node->symbol->type == LIT_CHAR)
			node->symbol->data_type = HASH_CHAR;
		if (node->symbol->type == LIT_STRING)
			node->symbol->data_type = HASH_STRING;
		if (node->symbol->type == LIT_FALSE)
			node->symbol->data_type = HASH_BOOL;
		if (node->symbol->type == LIT_TRUE)
			node->symbol->data_type = HASH_BOOL;
	}


	return node->type;


}
