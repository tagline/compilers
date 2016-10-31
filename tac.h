//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include "hash.h"

#define TAC_ADD 1
#define TAC_SUB 2
#define TAC_MUL 3
#define TAC_DIV 4 
#define TAC_GREATER 5
#define TAC_LESS 6
#define TAC_LE 7 
#define TAC_GE 8 
#define TAC_EQUAL 9	 
#define TAC_NEQUAL 10 
#define TAC_OR 11
#define TAC_AND 12
#define TAC_SYMBOL 13
#define TAC_LABEL 14
#define TAC_BEGINFUN 15
#define TAC_ENDFUN 16
#define TAC_IFZ 17
#define TAC_JUMP 18
#define TAC_CALL 19
#define TAC_ARG 20
#define TAC_RET 21
#define TAC_MOVE 22
#define TAC_PRINT 23
#define TAC_RETURN 24
#define TAC_ATRIB 25

typedef struct tac
{
	int type;
	HASH_NODE *res;	
	HASH_NODE *op1;	
	HASH_NODE *op2;	
	struct tac *prev;
	struct tac *next;
} TAC;


TAC* tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
TAC* tacJoin(TAC* l1,TAC* l2);
void tacPrintSingle(TAC *node);
void tacPrintList(TAC *node);
TAC* generateCode(TAC *node);
TAC *tacReverse(TAC *tac);

