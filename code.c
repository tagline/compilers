
#include <stdio.h>
#include "code.h"

TAC* makeBinOp(int op, TAC** code);

TAC *generateCode(ASTREE *node) 
{
	if(node == 0) return NULL;

	int i=0;
	TAC* code[MAX_SONS] = {0,0,0,0};

	if(!node) return 0;

	for(i=0; i<MAX_SONS; i++)
		code[i] = generateCode(node->son[i]);	

	switch(node->type)
	{
		case ASTREE_SYMBOL: 	return tacCreate(TAC_SYMBOL, node->symbol,0,0); break;
		case ASTREE_ADD : 	return makeBinOp(TAC_ADD, code); break;
		case ASTREE_SUB : 	return makeBinOp(TAC_SUB,code); break;
		case ASTREE_MUL : 	return makeBinOp(TAC_MUL,code); break;
		case ASTREE_DIV : 	return makeBinOp(TAC_DIV,code); break;

		case ASTREE_MENOR: 	return makeBinOp(TAC_MENOR,code); break;
		case ASTREE_MAIOR: 	return makeBinOp(TAC_MAIOR,code); break;
		case ASTREE_LE: 	return makeBinOp(TAC_LE,code); break;
		case ASTREE_GE: 	return makeBinOp(TAC_GE,code); break;
		case ASTREE_EQ: 	return makeBinOp(TAC_EQ,code); break;
		case ASTREE_NE: 	return makeBinOp(TAC_NE,code); break;
		case ASTREE_AND: 	return makeBinOp(TAC_AND,code); break;
		case ASTREE_OR: 	return makeBinOp(TAC_OR,code); break;

		case ASTREE_INT: 	return tacCreate(TAC_INT, 0, 0, 0); break;
		case ASTREE_FLOAT: 	return tacCreate(TAC_FLOAT, 0, 0, 0); break;
		case ASTREE_BOOL: 	return tacCreate(TAC_BOOL, 0, 0, 0); break;
		case ASTREE_CHAR: 	return tacCreate(TAC_CHAR, 0, 0, 0); break;
		
		case ASTREE_BLOCO: 	return code[0]; break;

		case ASTREE_CMD_ATRIBUICAO : return tacJoin(code[0], tacCreate(TAC_MOVE,node->symbol,code[0]?code[0]->res:0,0)); break;

		case ASTREE_VAZIO: 	break;
	}

	// default return
	return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);

}



TAC* makeBinOp(int op, TAC** code) 
{
	return tacJoin( code[0], 
			tacJoin( code[1],
				 tacCreate(op, makeTemp(), (code[0]?code[0]->res:0), (code[1]?code[1]->res:0)) 
			       )
			);
}


