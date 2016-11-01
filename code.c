
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


/*

TAC* makeIf(TAC* expr, TAC* then, TAC* els) {
	HASH_ELEMENT* targetElse = makeLabel();
	HASH_ELEMENT* targetEnd = makeLabel();

	TAC* jumpElse = tacCreate(TAC_JFALSE, targetElse, expr->res, 0);
	TAC* jumpEnd = tacCreate(TAC_JUMP, targetEnd, 0, 0);

	TAC* labelElse = tacCreate(TAC_LABEL, targetElse, 0, 0);
	TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(expr ,jumpElse), then), jumpEnd), labelElse), els), labelEnd);
}


TAC* makeWhile(TAC* expr, TAC* cmd) {
	HASH_ELEMENT* targetBegin = makeLabel();
	HASH_ELEMENT* targetEnd = makeLabel();

	TAC* jumpBegin = tacCreate(TAC_JUMP, targetBegin, 0, 0);
	TAC* jumpEnd = tacCreate(TAC_JFALSE, targetEnd, expr->res, 0);

	TAC* labelBegin = tacCreate(TAC_LABEL, targetBegin, 0, 0);
	TAC* labelEnd = tacCreate(TAC_LABEL, targetEnd, 0, 0);

	return tacJoin(tacJoin(tacJoin(tacJoin(tacJoin(labelBegin, expr), jumpEnd), cmd), jumpBegin), labelEnd);
}


TAC* funcDecl(HASH_ELEMENT* symbol, TAC* type, TAC* params, TAC* cmds) {
	TAC* beginf = tacCreate(TAC_BEGINF, symbol, 0, 0);
	TAC* endf = tacCreate(TAC_ENDF, symbol, 0, 0);

	return tacJoin(tacJoin(tacJoin(params, beginf), cmds), endf);

}

TAC* makeAtrVec(HASH_ELEMENT* symbol, TAC* exprIndex, TAC* cmd){
	TAC *codeList = 0;

	TAC *moveInd = tacCreate(TAC_MOVE_IND, symbol, exprIndex ? exprIndex->res : 0, cmd ? cmd->res : 0);
	codeList = tacJoin(tacJoin(exprIndex, cmd), moveInd);

	return codeList;
}
*/
