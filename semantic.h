//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#ifndef SEMANTIC_HEADER
#define SEMANTIC_HEADER

#include "astree.h"
#include "y.tab.h"

int setTypes(ASTREE *node);
void semanticError(int line, char *strError);
int compareTypesExp(int type1,int type2);
int compareNatures(ASTREE *node1,ASTREE *node2);
int checkExpression(ASTREE *node);
int checkSemantic(ASTREE *node);

#endif
