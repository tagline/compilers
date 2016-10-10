//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include "astree.h"

void setTypes(ASTREE *node)
{
	int i;
	
	if(!node) return;
	
	for(i=0; i<MAX_SONS;i++)
		setTypes(node->son[i]);

/*
	if(node->type == ASTREE_DECLARACOES) {

		if(node->type->symbol != ASTREE_SYMBOL) {
			fprintf(stdr,"Semantic Error at line number %d...", lineNumber);
		}

	}
*/

}
