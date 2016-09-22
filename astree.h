//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include "hash.h"

#define MAX_SONS 4 

#define ASTREE_UNKNOWN 0
#define ASTREE_SYMBOL 1
#define ASTREE_ATRIBUICAO 25

#define ASTREE_CMD_ATRIBUICAO 25
#define ASTREE_CMD_ATRIBUICAO_VETOR 26
#define ASTREE_CMD_IF 27
#define ASTREE_CMD_IF_ELSE 28
#define ASTREE_CMD_FOR 29
#define ASTREE_CMD_FOR_TO 30
#define ASTREE_CMD_READ 31
#define ASTREE_CMD_PRINT 32
#define ASTREE_CMD_RETURN 33

#define ASTREE_VETOR 34
#define ASTREE_CHAMADA_FUNCAO 35
#define ASTREE_EXP_PARENTESES 36
#define ASTREE_NEGACAO 37

#define ASTREE_ADD 38
#define ASTREE_SUB 39
#define ASTREE_MUL 40
#define ASTREE_DIV 41

#define ASTREE_MENOR 42
#define ASTREE_MAIOR 43
#define ASTREE_LE 44
#define ASTREE_GE 45
#define ASTREE_EQ 46
#define ASTREE_NE 47
#define ASTREE_AND 48
#define ASTREE_OR 49

#define ASTREE_ARGUMENTOS 50
#define ASTREE_RESTO_ARGUMENTOS 51


typedef struct astree_node
{
	// type: comando; assinalamento; soma; identificador (apenas aponta para a tabela de símbolos)
	int type; 
	HASH_NODE *symbol;
	struct astree_node *son[MAX_SONS];
	
} ASTREE;

ASTREE *astreeCreate(int type, HASH_NODE *symbol, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3);
void astreePrint(ASTREE *node, int level);

