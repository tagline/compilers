//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdlib.h>
#include "tac.h"


TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2)
{
	TAC *newTac = 0;

	newTac = (TAC*)calloc(1,sizeof(TAC));
	newTac->type = type;
	newTac->res = res;
	newTac->op1 = op1;
	newTac->op2 = op2;
	newTac->prev = 0;
	newTac->next = 0;	
	return newTac;
}

TAC * tacJoin(TAC *l1,TAC *l2)
{
	if(!l1) return l2;
	if(!l2) return l1;

	TAC *tac;

	for(tac = l2; tac->prev; tac = tac->prev)
		;

	tac->prev = l1;	
	return l2;
}


void tacPrintSingle(TAC *tac) 
{
	if (!tac) return;

	if(tac->type == TAC_SYMBOL) return;

	switch(tac->type)
	{
		case TAC_ADD: 		fprintf(stderr,"(TAC_ADD");break;
		case TAC_SUB: 		fprintf(stderr,"(TAC_SUB");break;
		case TAC_MUL: 		fprintf(stderr,"(TAC_MUL");break;
		case TAC_DIV: 		fprintf(stderr,"(TAC_DIV");break;

		case TAC_MAIOR:		fprintf(stderr,"(TAC_MAIOR");break;
		case TAC_MENOR:		fprintf(stderr,"(TAC_MENOR");break;
		case TAC_LE: 		fprintf(stderr,"(TAC_LE");break;
		case TAC_GE: 		fprintf(stderr,"(TAC_GE");break;
		case TAC_EQ:	 	fprintf(stderr,"(TAC_EQ");break;
		case TAC_NE:	 	fprintf(stderr,"(TAC_NE");break;
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
	        case TAC_ATRIBUICAO: 	fprintf(stderr, "(TAC_ATRIBUICAO");break;

		default: 		fprintf(stderr,"(UNKNOWN %d", tac->type); break;
	}

	if(tac->res) fprintf(stderr,",%s",tac->res->text); else fprintf(stderr,", ");
	if(tac->op1) fprintf(stderr,",%s",tac->op1->text); else fprintf(stderr,", ");
	if(tac->op2) fprintf(stderr,",%s",tac->op2->text); else fprintf(stderr,", ");
	
	fprintf(stderr,")\n");

}

//imprime de trás pra frente
void tacPrintList(TAC *tac) {	
	if(tac){
		tacPrintList(tac->prev);
		tacPrintSingle(tac);
	}
}

/*
TAC *tacReverse(TAC *tac){
	TAC *p;
	
	if (p){
		for (p=tac;p->prev!=0;p=p->prev){
			p->prev->next = p;
		}
	}
	return;
		
}
*/

