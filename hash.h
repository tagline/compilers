//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#ifndef HASH_HEADER
#define HASH_HEADER

# define HASH_SIZE 	997
# define HASH_INT 	2 
# define HASH_FLOAT 	3 
# define HASH_BOOL 	4 
# define HASH_CHAR 	1 
# define HASH_STRING 5
# define HASH_SCALAR 11
# define HASH_VECTOR 12
# define HASH_FUNCTION 13

typedef struct func_param
{
	int data_type;
	struct func_param * next;

} FUNC_PARAM;

typedef struct hash_node
{
	int type;
	int nature;
	int data_type;
	char *text;
	int line;
	int declared;
	struct func_param * parameters;
	struct hash_node * next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE* hashInsert(int type, char* text);
HASH_NODE* hashFind(char *text);
void hashPrint(void);
HASH_NODE* makeTemp(void);
HASH_NODE* makeLabel(void);

#endif

