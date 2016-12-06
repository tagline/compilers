
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
		
		case ASTREE_CMD_IF: 		  return makeIf(code); break;
		case ASTREE_CMD_IF_ELSE:	  return makeIfThen(code); break;
		case ASTREE_CMD_RETURN:		  return tacJoin(code[0], tacCreate(TAC_RETURN,code[0]?code[0]->res:0,0,0)); break;
		case ASTREE_CMD_READ: 		  return tacJoin(code[0], tacCreate(TAC_READ,code[0]?code[0]->res:0,0,0)); break;
		case ASTREE_CMD_PRINT:  	  return tacJoin(code[0], tacCreate(TAC_PRINT,code[0]?code[0]->res:0,code[1]?code[1]->res:0,0)); break;
		case ASTREE_CMD_ATRIBUICAO: 	  return tacJoin(code[0], tacCreate(TAC_MOVE,node->symbol,code[0]?code[0]->res:0,0)); break;
		case ASTREE_CMD_ATRIBUICAO_VETOR: return makeAtribVector(node->symbol,code); break; 
		case ASTREE_PARAMETROS: 	return tacJoin(code[0], tacCreate(TAC_PARAMETRO,node->symbol,code[0]?code[0]->res:0,0)); break;
		case ASTREE_DECLARACAO_FUNCAO:    return makeFuncDecl(node->symbol,code); break;
		case ASTREE_VARIAVEL:    	  return tacCreate(TAC_DECLAR_VARIAVEL, node->symbol, 0, 0);
		case ASTREE_VETOR_DECLARADO_1:    return tacCreate(TAC_DECLAR_VECTOR, node->symbol, code[1]?code[1]->res:0, 0);
		case ASTREE_VETOR_DECLARADO_2:	  return tacCreate(TAC_DECLAR_VECTOR, node->symbol, code[1]?code[1]->res:0, 0);
		case ASTREE_CHAMADA_FUNCAO:	  return tacJoin(code[0], tacCreate(TAC_CALL, makeTemp(), node->symbol, 0)); break;
		//case ASTREE_CMD_FOR: 		return makeFor(code); break;		
		
		case ASTREE_PROGRAMA:   return tacJoin(code[0], code[1]);break;
		case ASTREE_BLOCO: 	return code[0]; break;		
		case ASTREE_VAZIO: 	break;
	}

	// default return
	return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);

}



TAC* makeBinOp(int op, TAC** code) 
{
	return tacJoin(code[0], tacJoin( code[1],
				 	 tacCreate(op, makeTemp(), (code[0]?code[0]->res:0), (code[1]?code[1]->res:0)) 
			       		)
			);
}

TAC* makeIf(TAC** code) {
	TAC* t1;
	TAC* t2;
	HASH_NODE *newLabel;

	newLabel = makeLabel();

	t1 = tacCreate(TAC_IFZ,newLabel,code[0]?code[0]->res:0,0);
	t2 = tacCreate(TAC_LABEL,newLabel,0,0);

	return tacJoin(tacJoin(tacJoin(code[0],t1),code[1]),t2);
}

TAC* makeIfThen(TAC** code) { 
	TAC* t1;
	TAC* t2;
	HASH_NODE *newLabel;

	newLabel = makeLabel();

	t1 = tacCreate(TAC_IFZ,newLabel,code[0]?code[0]->res:0,code[1]?code[1]->res:0);
	t2 = tacCreate(TAC_LABEL,newLabel,0,0);

	return tacJoin(tacJoin(tacJoin(tacJoin(code[0],t1),code[1]),t2),code[3]);
}

TAC* makeFuncDecl(HASH_NODE* symbol, TAC** code) {
	
	TAC* beginFunc = tacCreate(TAC_BEGIN_FUN, symbol, 0, 0);
	TAC* endFunc   = tacCreate(TAC_END_FUN, symbol, 0, 0);

	return tacJoin(tacJoin(tacJoin(code[1], beginFunc), code[0]), endFunc);

}

TAC* makeAtribVector(HASH_NODE* symbol, TAC** code){
	
	return tacJoin(tacJoin(code[0], code[1]), tacCreate(TAC_MOVE_IND, symbol, (code[0]?code[0]->res:0), (code[1]?code[1]->res:0)));

}

/*
TAC* makeFor(TAC** node) {
	
}
*/


// ASM OUTPUT
void tac2asm (TAC*node, FILE *fout) 
{
	//printf("oi: %s",node->type);
	TAC* tac;
	for(tac = node; tac; tac = tac->prev)
	{
		printf("oi: %d",tac->type);
	
	switch(tac->type)
	{

		// dentro de cada uma desses cases imprimir o que o compilador gera de código (gerar um assembly depois ver o que o compilador gera de codigo)
		//case TAC_BEGIN_FUN : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_END_FUN : fprintf(fout, "\t.globl _%s\n"); break;
		case TAC_ADD : fprintf(fout, "\taddl\t%s, %s\n",node->res); break;
		//case TAC_SUB : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_MUL : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_DIV : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_MAIOR : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_MENOR : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_LE : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_GE : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_EQ : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_NE : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_OR : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_AND : fprintf(fout, "\t.globl _%s\n"); break;

		//case TAC_LABEL : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_BEGIN_FUN : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_END_FUN : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_IFZ : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_JUMP : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_CALL : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_MOVE : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_MOVE_IND : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_PRINT : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_RETURN : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_READ : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_ATRIBUICAO : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_SYMBOL : fprintf(fout, "\t.globl _%s\n"); break;

		//case TAC_INT : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_FLOAT : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_BOOL : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_CHAR : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_PARAMETRO : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_DECLAR_VECTOR : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_DECLAR_VARIAVEL : fprintf(fout, "\t.globl _%s\n"); break;
		//case TAC_ARGUMENTOS : fprintf(fout, "\t.globl _%s\n"); break;

		//case TAC_HEADER : fprintf(fout, "\t.globl _%s\n"); break;
		default: continue;
	}}
}

	
