//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include "tac.h"
#include "hash.c"
#include "astree.c"


TAC* makeBinOp(int op, TAC** code);


TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
	TAC *newTac;

	newTac = (TAC*)calloc(1,sizeof(TAC));
	newTac->type = type;
	newTac->res = res;
	newTac->op1 = op1;
	newTac->op2 = op2;
	newTac->prev = NULL;
	newTac->next = NULL;
	
	if (newTac)
		return newTac;
	else
		return NULL;
}


TAC* tacJoin(TAC* l1,TAC* l2)
{
	TAC *node;
	if(!l1) return l2;
		
	if(!l2) return l1;
	for(node = l2; node->prev; node = node->prev)
		;

	node->prev = l1;	
	return l2;
}


void tacPrintSingle(TAC *node) 
{
	if (!node) return;

	if(node->type == SYMBOL) return;

	switch(node->type)
	{
		case TAC_ADD: 		fprintf(stderr,"(TAC_ADD");break;
		case TAC_SUB: 		fprintf(stderr,"(TAC_SUB");break;
		case TAC_MUL: 		fprintf(stderr,"(TAC_MUL");break;
		case TAC_DIV: 		fprintf(stderr,"(TAC_DIV");break;
		case TAC_GREATER:	fprintf(stderr,"(TAC_GREATER");break;
		case TAC_LESS:		fprintf(stderr,"(TAC_LESS");break;
		case TAC_LE: 		fprintf(stderr,"(TAC_LE");break;
		case TAC_GE: 		fprintf(stderr,"(TAC_GE");break;
		case TAC_EQUAL: 	fprintf(stderr,"(TAC_EQUAL");break;
		case TAC_NEQUAL: 	fprintf(stderr,"(TAC_NEQUAL");break;
		case TAC_OR: 		fprintf(stderr,"(TAC_OR");break;
		case TAC_AND: 		fprintf(stderr,"(TAC_AND");break;
		case TAC_SYMBOL : 	fprintf(stderr, "(TAC_SYMBOL"); break;
		case TAC_LABEL :	fprintf(stderr, "(TAC_LABEL"); break;
		case TAC_BEGINFUN :	fprintf(stderr, "(TAC_BEGINFUN"); break;
		case TAC_ENDFUN :	fprintf(stderr, "(TAC_ENDFUN"); break;		
		case TAC_IFZ : 		fprintf(stderr, "(TAC_IFZ"); break;
		case TAC_JUMP : 	fprintf(stderr, "(TAC_JUMP"); break;
		case TAC_CALL : 	fprintf(stderr, "(TAC_CALL"); break;
		case TAC_ARG  : 	fprintf(stderr, "(TAC_ARG"); break;
		case TAC_RET  : 	fprintf(stderr, "(TAC_RET"); break;
		case TAC_MOVE : 	fprintf(stderr, "(TAC_MOVE"); break;
	        case TAC_PRINT: 	fprintf(stderr, "(TAC_PRINT"); break;
	        case TAC_RETURN : 	fprintf(stderr, "(TAC_RETURN"); break;
	        case TAC_ATRIB: 	fprintf(stderr, "(TAC_ATRIB");break;
		default: 		fprintf(stderr,"(UNKNOWN %d", node->type); break;
	}

	if(node->target) fprintf(stderr,",%s",node->target->text); else fprintf(stderr,",#");
	if(node->op1) fprintf(stderr,",%s",node->op1->text); else fprintf(stderr,",#");
	if(node->op2) fprintf(stderr,",%s",node->op2->text); else fprintf(stderr,",#");
	
	fprintf(stderr,");\n");

	i++;
}


void tacPrintList(TAC *first) 
{
	TAC *node;

	for(node = first;node;node = node->next)
		tacPrintSingle(node);

}

TAC *tacReverse(TAC *tac){
	TAC *p;
	
	if (p){
		for (p=tac;p->prev!=0;p=p->prev){
			p->prev->next = p;
		}
	}
	return;

		
}

TAC* generateCode(ASTREE *node) 
{
	int i=0;
	TAC* code[MAX_SONS] = {0,0,0,0};

	if(!node) return 0;

	for(i=0; i<MAX_SONS; i++)
		code[i] = generateCode(node->son[i]);	

	switch(node->type)
	{
		case ASTREE_SYMBOL: return tacCreate(TAC_SYMBOL, node->symbol,0,0); break;
		//case ASTREE_ADD : return makeBinOp(TAC_ADD,code); break;
		//case ASTREE_SUB : return makeBinOp(TAC_SUB,code); break;
		//case ASTREE_MUL : return makeBinOp(TAC_MUL,code); break;
		//case ASTREE_ATRIBUICAO : return tacJoin(code[0], tacCreate(TAC_MOVE,node->symbol,code[0]?code[0]->res:0,0)); break;
	}

	// default return
	return tacJoin(tacJoin(tacJoin(code[0],code[1]),code[2]),code[3]);

}


TAC* makeBinOp(int op, TAC** code) 
{
	return tacJoin(code[0],tacjoin(code[1],tacCreate(op,makeTemp(), code[0]?code[0]->res:0, code[1]?code[1]->res:0)));
}

