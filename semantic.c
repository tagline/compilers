//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include <stdlib.h>

#include "semantic.h"

int currFuncType = 0;

void semanticError(int line, char *strError)
{

	printf ("Semantic Error in line number %d : %s \n", line, strError);
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
			semanticError(node->line, "VAR Undeclared or Redeclared");


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
			semanticError(node->line, "FUNCTION Undeclared or Redeclared");

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
			semanticError(node->line, "VECTOR Undeclared or Redeclared");

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
	if (type1 == 0 || type2 == 0){
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

int findNature (ASTREE *node)
{
	if (node->type == ASTREE_VETOR || node->type == ASTREE_CHAMADA_FUNCAO)
		return HASH_SCALAR;

	if (node->symbol)
		return node->symbol->nature;
	else
		return findNature (node->son[0]);
}

int compareNatures(ASTREE *node1,ASTREE *node2)
{
	int nature1 = findNature(node1);
	int nature2 = findNature(node2);
	if(nature1 == nature2)
		return nature1;
	semanticError(node1->line, "");
}

int checkFuncArguments (ASTREE *node, FUNC_PARAM * parameters)
{
	//if function should have no parameter -> error
	if (parameters == NULL)
		semanticError(node->line, "No parameters");

	//if argument not scalar -> error
	if (findNature(node->son[0])!=HASH_SCALAR)
		semanticError(node->line, "Argument Invalid");

	if (checkExpression (node->son[0]) == parameters->data_type){
		if (node->son[1])
		{
			if (parameters->next == NULL)
				semanticError(node->line,"Argument Invalid");
			checkFuncArguments (node->son[1], parameters->next);
		}
	}
	else
		semanticError(node->line,"");
	if (parameters->next != NULL)
		if(node->son[1] == NULL)
			semanticError(node->line,"Argument Invalid");


}

int checkExpression(ASTREE *node)
{
	int expType = 0;
	if (node->type == ASTREE_SYMBOL){
		if (node->symbol->data_type == 0)
			semanticError(node->line,"Datatype Invalid");
		return node->symbol->data_type;
	}

	if (node->type == ASTREE_EXP_PARENTESES)
		return checkExpression(node->son[0]);

	if (node->type == ASTREE_VETOR){

		//Vector has to be a declared vector
		if(node->symbol->nature != HASH_VECTOR)
			semanticError(node->line,"Vector not Declared");

		//Vector index has to be int
		if(checkExpression(node->son[0])!= HASH_INT)
			semanticError(node->line,"A vector index must be INTEGER");
		return node->symbol->data_type;
	}

	if (node->type == ASTREE_CHAMADA_FUNCAO){
		if (node->symbol->nature != HASH_FUNCTION)
			semanticError(node->line,"Call FUNCTION");
		checkFuncArguments(node->son[0],node->symbol->parameters);
		return node->symbol->data_type;
	}
	
	if (node->type == ASTREE_NEGACAO)
		return checkExpression(node->son[0]);

	if(node->son[0]->symbol && node->son[1]->symbol){
		expType = compareTypesExp(node->son[0]->symbol->data_type,node->son[1]->symbol->data_type);
		if(expType == -1)
			semanticError(node->line," Wrong Use of !");
		if(compareNatures(node->son[0],node->son[1]))
			return expType;
		else
			semanticError(node->line,"Operators Invalid");
	}
	return(compareTypesExp(checkExpression(node->son[0]),checkExpression(node->son[1])));	
}

int checkAttribution(ASTREE *node)
{
	//Not string or undefined
	if (node->symbol->data_type>4||node->symbol->data_type==0)
		semanticError(node->line,"Incorrect ATTRIBUTION");
	compareNatures (node, node->son[0]);

	//BOOL with BOOL
	if (node->symbol->data_type == HASH_BOOL){
		if (checkExpression(node->son[0])==HASH_BOOL)
			return HASH_BOOL;
		else
			semanticError(node->line,"Incorrect ATTRIBUTION");
		}
	//FLOAT INT CHAR
	if (node->symbol->data_type>=checkExpression(node->son[0]))
		return node->symbol->data_type;
	semanticError(node->line,"Incorrect ATTRIBUTION");

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
	//checkSemantic(node->son[1]);
}

int checkFORTO(ASTREE *node)
{
	//Control
	int controlType = 0;
	controlType = compareTypesExp(checkExpression(node->son[0]),node->symbol->data_type);
	if(controlType)
	{
		if(compareTypesExp(controlType,checkExpression(node->son[1]))==-1)
			semanticError(node->line,"Wrong command FOR TO");
		//Command
		//checkSemantic(node->son[2]);
	}
	else
		semanticError(node->line,"Wrong command FOR TO");
}

int checkREAD(ASTREE *node)
{
	if (node->symbol->declared == 0)
		semanticError(node->line,"Wrong command READ");
}

int checkPrint(ASTREE *node)
{
	
	if (node->symbol)
		if (node->symbol->data_type != HASH_STRING)
			semanticError(node->line,"Wrong command PRINT");
	
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
	FUNC_PARAM *test;
	test = function->parameters;
	newparam->data_type = node->symbol->data_type;
	newparam->next = NULL;

	if (function->parameters == NULL){
		function->parameters = newparam;
		if(node->son[1])
			saveParameters (node->son[1],function);
	}
	else{
		while (test->next != NULL)
			test = test->next;
		test->next = newparam;
		if(node->son[1])
			saveParameters (node->son[1],function);
	}
}

int checkFunction (ASTREE *node)
{
	currFuncType = node->symbol->data_type;

	if (currFuncType == 0 || currFuncType > 4)
		semanticError(node->line,"DataType Invalid");
	if (node->son[1])
		saveParameters(node->son[1],node->symbol);
	if (node->son[2])
		checkSemantic(node->son[3]);
}

int checkReturn (ASTREE *node)
{
	//printf("Func Type = %d", currFuncType);
	//printf("Type = %d", checkExpression(node->son[0]));
	if (currFuncType != checkExpression(node->son[0]))
		semanticError(node->line,"Wrong command RETURN");
}

int checkVectorValues (ASTREE *node,int type)
{
	//printf("Func Type = %d", type);
	//printf("Type = %d", node->son[0]->symbol->data_type);
	
	int value;
	value = node->son[0]->symbol->data_type;
	if (type == HASH_BOOL)
		if (value!=HASH_BOOL)
			semanticError(node->line,"Invalid value - expected a BOOL");
	if (value>type || value>HASH_BOOL || value ==0)
		semanticError(node->line,"Invalid value - expected a BOOL");
	if (node->son[1])
		checkVectorValues (node->son[1],type);

}

int checkVectorDec (ASTREE *node)
{
	//printf("Type = %d", node->son[1]->symbol->data_type);
	
	if (node->son[1]->symbol->data_type!=HASH_INT)
		semanticError(node->line,"VECTOR wrong Declared");

	if (node->son[2])
		checkVectorValues(node->son[2],node->symbol->data_type);

}

int checkVar (ASTREE *node)
{
	if (compareTypesExp(node->symbol->data_type,node->son[1]->symbol->data_type)==-1)
		semanticError(node->line,"VAR wrong Declared");

}

int checkSemantic(ASTREE *node)
{
	if(node)
	{
		switch(node->type)
		{	
			case ASTREE_SYMBOL :			checkExpression(node);break;
			case ASTREE_CMD_ATRIBUICAO : 		checkAttribution(node);break;
			case ASTREE_CMD_IF : 			checkIF(node);break;
			case ASTREE_CMD_IF_ELSE : 		checkIF(node);break;
			case ASTREE_CMD_FOR : 			checkFOR(node);break;
			case ASTREE_CMD_FOR_TO : 		checkFORTO(node);break;
			case ASTREE_CMD_READ : 			checkREAD(node);break;
			case ASTREE_CMD_PRINT : 		checkPrint(node);break;
			case ASTREE_CMD_RETURN : 		checkReturn(node);break;
			case ASTREE_VETOR : 			checkExpression(node);break;
			case ASTREE_CHAMADA_FUNCAO : 		checkExpression(node);break;
			case ASTREE_EXP_PARENTESES: 		checkExpression(node);break;
			case ASTREE_NEGACAO : 			checkExpression(node);break;
			case ASTREE_ADD : 			checkExpression(node);break;
			case ASTREE_SUB : 			checkExpression(node);break;
			case ASTREE_MUL : 			checkExpression(node);break;
			case ASTREE_DIV : 			checkExpression(node);break;
			case ASTREE_MENOR : 			checkExpression(node);break;
			case ASTREE_MAIOR : 			checkExpression(node);break;
			case ASTREE_LE : 			checkExpression(node);break;
			case ASTREE_GE : 			checkExpression(node);break;
			case ASTREE_EQ : 			checkExpression(node);break;
			case ASTREE_NE : 			checkExpression(node);break;
			case ASTREE_AND : 			checkExpression(node);break;
			case ASTREE_OR : 			checkExpression(node);break;
			case ASTREE_ARGUMENTOS : 		break;	//ja feito
			case ASTREE_RESTO_ARGUMENTOS : 		break;	//ja feito
			case ASTREE_LISTA_COMANDOS :		break;	//ja feito
			case ASTREE_COMANDOS :			break;	//ja feito
			case ASTREE_LISTA_DECLARACOES :		break;	//ja feito
			case ASTREE_DECLARACOES :		break;	//ja feito
			case ASTREE_VARIAVEL :			checkVar (node);break;
			case ASTREE_VETOR_DECLARADO_1 :		checkVectorDec (node);break;
			case ASTREE_VETOR_DECLARADO_2 :		checkVectorDec (node);break;
			case ASTREE_INT :			break;	//ja feito
			case ASTREE_FLOAT :			break;	//ja feito
			case ASTREE_BOOL :			break;	//ja feito
			case ASTREE_CHAR :			break;	//ja feito
			case ASTREE_DECLARACAO_FUNCAO:		checkFunction(node);break;
			case ASTREE_BLOCO :			break;	//ja feito
			case ASTREE_PARAMETROS:			break;	//ja feito
			case ASTREE_PARAMETROS_RESTO:		break;	//ja feito		
			case ASTREE_PROGRAMA:			break;	//ja feito
			case ASTREE_VETOR_CONTEUDO:		break;	//ja feito	
			default: 				break;			
		}

		int i;

		for(i=0; i<MAX_SONS; i++)
		{
			checkSemantic(node->son[i]);		
		}

	}
	

}

