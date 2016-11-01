//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#ifndef TAC_HEADER
#define TAC_HEADER

#include <stdio.h>
#include "hash.h"

#define TAC_ADD 1
#define TAC_SUB 2
#define TAC_MUL 3
#define TAC_DIV 4 

#define TAC_MAIOR 5
#define TAC_MENOR 6
#define TAC_LE 7 
#define TAC_GE 8 
#define TAC_EQ 9	 
#define TAC_NE 10 
#define TAC_OR 11
#define TAC_AND 12

#define TAC_LABEL 13
#define TAC_BEGINFUN 14
#define TAC_ENDFUN 15
#define TAC_IFZ 16
#define TAC_JUMP 17
#define TAC_CALL 18
#define TAC_MOVE 19
#define TAC_MOVE_IND 20
#define TAC_PRINT 21
#define TAC_RETURN 22
#define TAC_READ 23
#define TAC_ATRIBUICAO 24
#define TAC_SYMBOL 25

#define TAC_INT 26
#define TAC_FLOAT 27
#define TAC_CHAR 28
#define TAC_BOOL 29

#define TAC_PARAMETRO 30
#define TAC_DECL_VECTOR 31
#define TAC_DECL_VARIAVEL 32
#define TAC_ARGUMENTOS 33


typedef struct tac
{
	int type;
	HASH_NODE *res;	
	HASH_NODE *op1;	
	HASH_NODE *op2;	
	struct tac *prev;
	struct tac *next;
} TAC;


TAC * tacCreate(int type, HASH_NODE *res, HASH_NODE *op1, HASH_NODE *op2);
TAC * tacJoin(TAC *l1,TAC *l2);
void tacPrintSingle(TAC *tac);
void tacPrintList(TAC *tac);
//TAC* tacReverse(TAC *tac);


#endif

