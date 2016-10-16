//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

int currFuncType = 0;

void semanticError(int line)
{
	printf ("Semantic Error: in line number %d\n", line);
	exit(4);
}

int setTypes(ASTREE *node)
{
	int i;
	
	if(!node) return -1;
	
	for(i=0; i<MAX_SONS;i++)
		setTypes(node->son[i]);
	

	if (node->type == ASTREE_VARIAVEL||
		node->type == ASTREE_PARAMETROS||
		node->type == ASTREE_PARAMETROS_RESTO
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (sonType == ASTREE_FLOAT){
			node->symbol->data_type = HASH_FLOAT;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (sonType == ASTREE_BOOL){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (sonType == ASTREE_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_SCALAR;
		}
		if(node->symbol->declared == 0)
			node->symbol->declared = 1;
		else
			semanticError(node->line);

	}

	if (node->type == ASTREE_DECLARACAO_FUNCAO
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_FUNCTION;
		}
		if (sonType == ASTREE_FLOAT){
			node->symbol->data_type = HASH_FLOAT;
			node->symbol->nature	= HASH_FUNCTION;
		}
		if (sonType == ASTREE_BOOL){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_FUNCTION;
		}
		if (sonType == ASTREE_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_FUNCTION;
		}

		if(node->symbol->declared == 0)
			node->symbol->declared = 1;
		else
			semanticError(node->line);

	}

	if (node->type ==ASTREE_VETOR_DECLARADO_1||
		node->type ==ASTREE_VETOR_DECLARADO_2
		) 
	{
		int sonType;
		sonType = setTypes(node->son[0]);
		if (sonType == ASTREE_INT){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_VECTOR;
		}
		if (sonType == ASTREE_FLOAT){
			node->symbol->data_type = HASH_FLOAT;
			node->symbol->nature	= HASH_VECTOR;
		}
		if (sonType == ASTREE_BOOL){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_VECTOR;
		}
		if (sonType == ASTREE_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_VECTOR;
		}

		if(node->symbol->declared == 0)
			node->symbol->declared = 1;
		else
			semanticError(node->line);

	}


	if (node->symbol)
	{
		if (node->symbol->type == LIT_INTEGER){
			node->symbol->data_type = HASH_INT;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_CHAR){
			node->symbol->data_type = HASH_CHAR;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_STRING){
			node->symbol->data_type = HASH_STRING;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_FALSE){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_SCALAR;
		}
		if (node->symbol->type == LIT_TRUE){
			node->symbol->data_type = HASH_BOOL;
			node->symbol->nature	= HASH_SCALAR;
		}
	}


	return node->type;
}

int compareTypesExp(int type1,int type2)
{
	if (type1 == 0 && type2 == 0){
		return -1;
	}
	//Dois Booleanos
	if (type1 == HASH_BOOL && type2 == HASH_BOOL)
		return HASH_BOOL;
	//Pelo menos um float
	if (type1 == HASH_FLOAT)
		if (type2 == HASH_FLOAT 
			|| type2== HASH_CHAR
			|| type2 == HASH_INT)
			return HASH_FLOAT;
	if (type2 == HASH_FLOAT)
		if (type1 == HASH_FLOAT 
			|| type1 == HASH_CHAR
			|| type1 == HASH_INT)
			return HASH_FLOAT;
	//Pelo menos um int
	if (type1 == HASH_INT)
		if (type2 == HASH_CHAR
			|| type2 == HASH_INT)
			return HASH_INT;
	if (type2 == HASH_INT)
		if (type1 == HASH_CHAR
			|| type1 == HASH_INT)
			return HASH_INT;
	//Dois char
	if (type1 == HASH_CHAR && type2 == HASH_CHAR)
		return HASH_CHAR;		

	else{
		return -1;
	}
}

int compareNatures(ASTREE *node1,ASTREE *node2)
{
	if(node1->symbol->nature == node2->symbol->nature)
		return node1->symbol->nature;
	semanticError(node1->line);
}

int checkFuncArguments (ASTREE *node)
{


}

int checkExpression(ASTREE *node)
{
	int expType = 0;
	if (node->type == ASTREE_SYMBOL){
		if (node->symbol->data_type == 0)
			semanticError(node->line);
		return node->symbol->data_type;
	}

	if (node->type == ASTREE_EXP_PARENTESES)
		return checkExpression(node->son[0]);

	if (node->type == ASTREE_VETOR){
		//Vector has to be a declared vector
		if(node->symbol->nature != HASH_VECTOR)
			semanticError(node->line);
		//Vector index has to be int
		if(checkExpression(node->son[0])!= HASH_INT)
			semanticError(node->line);
		return node->symbol->data_type;
	}

	if (node->type == ASTREE_CHAMADA_FUNCAO){
		if (node->symbol->nature != HASH_FUNCTION)
			semanticError(node->line);
		checkFuncArguments(node->son[0]);
		return node->symbol->data_type;
	}
	
	if (node->type == ASTREE_NEGACAO)
		return checkExpression(node->son[0]);

	if(node->son[0]->symbol && node->son[1]->symbol){
		expType = compareTypesExp(node->son[0]->symbol->data_type,node->son[1]->symbol->data_type);
		if(expType == -1)
			semanticError(node->line);
		if(compareNatures(node->son[0],node->son[1]))
			return expType;
		else
			semanticError(node->line);
	}
	return(compareTypesExp(checkExpression(node->son[0]),checkExpression(node->son[1])));	
}

int checkAttribution(ASTREE *node)
{
	//Not string or undefined
	if (node->symbol->data_type>4||node->symbol->data_type==0)
		semanticError(node->line);
	//BOOL with BOOL
	if (node->symbol->data_type == HASH_BOOL){
		if (checkExpression(node->son[0])==HASH_BOOL)
			return HASH_BOOL;
		else
			semanticError(node->line);
		}
	//FLOAT INT CHAR
	if (node->symbol->data_type>=checkExpression(node->son[0]))
		return node->symbol->data_type;
	semanticError(node->line);

}

int checkIF(ASTREE *node)
{
	//Condition
	checkExpression(node->son[0]);
	//Then
	checkSemantic(node->son[1]);
	//Else
	if (node->type == ASTREE_CMD_IF_ELSE)
		checkSemantic(node->son[2]);
}

int checkFOR(ASTREE *node)
{
	//Control
	checkExpression(node->son[0]);
	//Command
	checkSemantic(node->son[1]);
}

int checkFORTO(ASTREE *node)
{
	//Control
	int controlType = 0;
	controlType = compareTypesExp(checkExpression(node->son[0]),node->symbol->data_type);
	if(controlType)
	{
	if(compareTypesExp(controlType,checkExpression(node->son[1]))==-1);
		semanticError(node->line);
	//Command
	checkSemantic(node->son[2]);
	}
	else
		semanticError(node->line);
}

int checkREAD(ASTREE *node)
{
	if (node->symbol->declared == 0)
		semanticError(node->line);
}

int checkPrint(ASTREE *node)
{
	if (node->symbol)
		if (node->symbol->data_type != HASH_STRING)
			semanticError(node->line);
	if (node->son[0]){
		checkSemantic(node->son[0]);
	}
	if (node->son[1]){
		checkSemantic(node->son[1]);
	}
}

int saveParameters (ASTREE *node,HASH_NODE *function)
{
	FUNC_PARAM *newparam= malloc(sizeof(FUNC_PARAM));
//	function->parameters

}

int checkBlock (ASTREE *node, int funcType)
{


}

int checkFunction (ASTREE *node)
{
	currFuncType = node->symbol->data_type;

	if (currFuncType == 0 || currFuncType > 4)
		semanticError(node->line);
	if (node->son[1])
		saveParameters(node->son[1],node->symbol);
	if (node->son[2])
		checkSemantic(node->son[3]);
}

int checkReturn (ASTREE *node)
{
//	printf("Func Type = %d", currFuncType);
//	printf("Type = %d", checkExpression(node->son[0]));
	if (currFuncType != checkExpression(node->son[0]))
		semanticError(node->line);
}

int checkVectorValues (ASTREE *node,int type)
{
	printf("Func Type = %d", type);
	printf("Type = %d", node->son[0]->symbol->data_type);
	if (node->son[0]->symbol->data_type!=type)
		semanticError(node->line);
	if (node->son[1])
		checkVectorValues (node->son[1],type);

}

int checkVectorDec (ASTREE *node)
{
	printf("Type = %d", node->son[1]->symbol->data_type);
	if (node->son[1]->symbol->data_type!=HASH_INT)
		semanticError(node->line);
	if (node->son[2])
		checkVectorValues(node->son[2],node->symbol->data_type);

}

int checkSemantic(ASTREE *node)
{
	if(node)
	{
		switch(node->type)
		{	
			case ASTREE_SYMBOL :			checkExpression(node);break;
			case ASTREE_CMD_ATRIBUICAO : 	checkAttribution(node);break;
			case ASTREE_CMD_IF : 			checkIF(node);break;
			case ASTREE_CMD_IF_ELSE : 		checkIF(node);break;
			case ASTREE_CMD_FOR : 			checkFOR(node);break;
			case ASTREE_CMD_FOR_TO : 		checkFORTO(node);break;
			case ASTREE_CMD_READ : 			checkREAD(node);break;
			case ASTREE_CMD_PRINT : 		checkPrint(node);break;
			case ASTREE_CMD_RETURN : 		checkReturn(node);break;
			case ASTREE_VETOR : 			checkExpression(node);break;
			case ASTREE_CHAMADA_FUNCAO : 	checkExpression(node);break;
			case ASTREE_EXP_PARENTESES: 	checkExpression(node);break;
			case ASTREE_NEGACAO : 			checkExpression(node);break;
			case ASTREE_ADD : 				checkExpression(node);break;
			case ASTREE_SUB : 				checkExpression(node);break;
			case ASTREE_MUL : 				checkExpression(node);break;
			case ASTREE_DIV : 				checkExpression(node);break;
			case ASTREE_MENOR : 			checkExpression(node);break;
			case ASTREE_MAIOR : 			checkExpression(node);break;
			case ASTREE_LE : 				checkExpression(node);break;
			case ASTREE_GE : 				checkExpression(node);break;
			case ASTREE_EQ : 				checkExpression(node);break;
			case ASTREE_NE : 				checkExpression(node);break;
			case ASTREE_AND : 				checkExpression(node);break;
			case ASTREE_OR : 				checkExpression(node);break;
			case ASTREE_ARGUMENTOS : 		break;
			case ASTREE_RESTO_ARGUMENTOS : 	break;
			case ASTREE_LISTA_COMANDOS :	break;
			case ASTREE_COMANDOS :			break;
			case ASTREE_LISTA_DECLARACOES :	break;
			case ASTREE_DECLARACOES :		break;
			case ASTREE_VARIAVEL :			break;
			case ASTREE_VETOR_DECLARADO_1 :	checkVectorDec (node);break;
			case ASTREE_VETOR_DECLARADO_2 :	checkVectorDec (node);break;
			case ASTREE_INT :				break;
			case ASTREE_FLOAT :				break;
			case ASTREE_BOOL :				break;
			case ASTREE_CHAR :				break;
			case ASTREE_DECLARACAO_FUNCAO:	checkFunction(node);break;
			case ASTREE_BLOCO :				break;
			case ASTREE_PARAMETROS:			break;
			case ASTREE_PARAMETROS_RESTO:	break;			
			case ASTREE_PROGRAMA:			break;
			case ASTREE_VETOR_CONTEUDO:		break;		
			default: 						break;			
		}

		int i;

		for(i=0; i<MAX_SONS; i++)
		{
			checkSemantic(node->son[i]);		
		}

	}
	

}

