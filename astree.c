//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "astree.h"


extern FILE *fileout;

ASTREE *astreeCreate(int type, HASH_NODE *symbol, ASTREE *son0, ASTREE *son1, ASTREE *son2, ASTREE *son3,int line) 
{
	ASTREE *newNode = 0;

	newNode = (ASTREE*) calloc(1,sizeof(ASTREE));

	newNode->type   = type;
	newNode->symbol = symbol;	

	newNode->son[0] = son0;
	newNode->son[1] = son1;
	newNode->son[2] = son2;
	newNode->son[3] = son3;
	newNode->line = line;
	return newNode;
}


void astreePrint(ASTREE *node, int level)
{
	int i;

	if(node) 
	{
		for(i=0; i<level; i++)
			fprintf(stderr, " ");
		/*if(node->symbol)		//printa num linha
			fprintf(stderr, "Linha: %d\n",node->symbol->line);
		*/
		fprintf(stderr, "ASTREE( ");

		switch(node->type)
		{
			case ASTREE_SYMBOL :	 		fprintf(stderr, "ASTREE_SYMBOL"); break;			
			case ASTREE_CMD_ATRIBUICAO : 	fprintf(stderr, "ASTREE_CMD_ATRIBUICAO"); break;
			case ASTREE_CMD_IF : 			fprintf(stderr, "ASTREE_CMD_IF"); break;
			case ASTREE_CMD_IF_ELSE : 		fprintf(stderr, "ASTREE_CMD_IF_ELSE"); break;
			case ASTREE_CMD_FOR : 			fprintf(stderr, "ASTREE_CMD_FOR"); break;
			case ASTREE_CMD_FOR_TO : 		fprintf(stderr, "ASTREE_CMD_FOR_TO"); break;
			case ASTREE_CMD_READ : 			fprintf(stderr, "ASTREE_CMD_READ"); break;
			case ASTREE_CMD_PRINT : 		fprintf(stderr, "ASTREE_CMD_PRINT"); break;
			case ASTREE_CMD_RETURN : 		fprintf(stderr, "ASTREE_CMD_RETURN"); break;
			case ASTREE_VETOR : 			fprintf(stderr, "ASTREE_VETOR"); break;
			case ASTREE_CHAMADA_FUNCAO : 	fprintf(stderr, "ASTREE_CHAMADA_FUNCAO"); break;
			case ASTREE_EXP_PARENTESES: 	fprintf(stderr, "ASTREE_EXP_PARENTESES"); break;
			case ASTREE_NEGACAO : 			fprintf(stderr, "ASTREE_NEGACAO"); break;
			case ASTREE_ADD : 				fprintf(stderr, "ASTREE_ADD"); break;
			case ASTREE_SUB : 				fprintf(stderr, "ASTREE_SUB"); break;
			case ASTREE_MUL : 				fprintf(stderr, "ASTREE_MUL"); break;
			case ASTREE_DIV : 				fprintf(stderr, "ASTREE_DIV"); break;
			case ASTREE_MENOR : 			fprintf(stderr, "ASTREE_MENOR"); break;
			case ASTREE_MAIOR : 			fprintf(stderr, "ASTREE_MAIOR"); break;
			case ASTREE_LE : 				fprintf(stderr, "ASTREE_LE"); break;
			case ASTREE_GE : 				fprintf(stderr, "ASTREE_GE"); break;
			case ASTREE_EQ : 				fprintf(stderr, "ASTREE_EQ"); break;
			case ASTREE_NE : 				fprintf(stderr, "ASTREE_NE"); break;
			case ASTREE_AND : 				fprintf(stderr, "ASTREE_AND"); break;
			case ASTREE_OR : 				fprintf(stderr, "ASTREE_OR"); break;
			case ASTREE_ARGUMENTOS : 		fprintf(stderr, "ASTREE_ARGUMENTOS"); break;
			case ASTREE_RESTO_ARGUMENTOS : 	fprintf(stderr, "ASTREE_RESTO_ARGUMENTOS"); break;
			case ASTREE_LISTA_COMANDOS :	fprintf(stderr, "ASTREE_LISTA_COMANDOS"); break;
			case ASTREE_COMANDOS :			fprintf(stderr, "ASTREE_COMANDOS"); break;
			case ASTREE_LISTA_DECLARACOES :	fprintf(stderr, "ASTREE_LISTA_DECLARACOES"); break;
			case ASTREE_DECLARACOES :		fprintf(stderr, "ASTREE_DECLARACOES"); break;
			case ASTREE_VARIAVEL :			fprintf(stderr, "ASTREE_VARIAVEL"); break;
			case ASTREE_VETOR_DECLARADO_1 :	fprintf(stderr, "ASTREE_VETOR_DECLARADO_1"); break;
			case ASTREE_VETOR_DECLARADO_2 :	fprintf(stderr, "ASTREE_VETOR_DECLARADO_2"); break;
			case ASTREE_INT :				fprintf(stderr, "ASTREE_INT"); break;
			case ASTREE_FLOAT :				fprintf(stderr, "ASTREE_FLOAT"); break;
			case ASTREE_BOOL :				fprintf(stderr, "ASTREE_BOOL"); break;
			case ASTREE_CHAR :				fprintf(stderr, "ASTREE_CHAR"); break;
			case ASTREE_DECLARACAO_FUNCAO:	fprintf(stderr, "ASTREE_DECLARACAO_FUNCAO"); break;
			case ASTREE_BLOCO :				fprintf(stderr, "ASTREE_BLOCO"); break;
			case ASTREE_PARAMETROS:			fprintf(stderr, "ASTREE_PARAMETROS"); break;
			case ASTREE_PARAMETROS_RESTO:	fprintf(stderr, "ASTREE_PARAMETROS_RESTO"); break;			
			case ASTREE_PROGRAMA:			fprintf(stderr, "ASTREE_PROGRAMA"); break;
			case ASTREE_VETOR_CONTEUDO:		fprintf(stderr, "ASTREE_VETOR_CONTEUDO"); break;	
			case ASTREE_CMD_ATRIBUICAO_VETOR :		fprintf(stderr, "ASTREE_CMD_ATRIBUICAO_VETOR "); break;
			default: 						fprintf(stderr, "ASTREE_UNKNOWN %d",node->type); break;			
		}
		
		fprintf(stderr,",");
		

		if(node->symbol) {
			fprintf(stderr, "%s, Type: %d) \n", node->symbol->text, node->symbol->data_type);
		}
		else
			fprintf(stderr," \n");

	
		// chamada recursivamente para os filhos
		for(i=0; i<MAX_SONS; i++)
			astreePrint(node->son[i],level+1);		
	
	}

}

void astreeDecompile(ASTREE *astree, int node_father){

		if (astree)
		{
			
			switch(astree->type)
			{
				
				//---- Estruturas da Linguagem -----//
				
				case ASTREE_PROGRAMA:
					astreeDecompile(astree->son[0],ASTREE_PROGRAMA);
					fprintf(fileout, "PROGRAMA\n\n");
					break;
					
				case ASTREE_LISTA_DECLARACOES:
					astreeDecompile(astree->son[0],ASTREE_LISTA_DECLARACOES);
					astreeDecompile(astree->son[1],ASTREE_LISTA_DECLARACOES);
					break;

				case ASTREE_DECLARACOES:					
					astreeDecompile(astree->son[0],ASTREE_DECLARACOES);
					fprintf(fileout, ";\n");
					break;
	
				case ASTREE_VARIAVEL:
					astreeDecompile(astree->son[0],ASTREE_VARIAVEL);
					fprintf(fileout," %s:",astree->symbol->text);
					astreeDecompile(astree->son[1],ASTREE_VARIAVEL);
					break;

				case ASTREE_VETOR:
					fprintf(fileout,"%s[",astree->symbol->text);
					astreeDecompile(astree->son[0],ASTREE_VETOR);
					fprintf(fileout, "]");
					break;
				
				case ASTREE_VETOR_DECLARADO_1:				
					astreeDecompile(astree->son[0],ASTREE_VETOR_DECLARADO_1);
					fprintf(fileout," %s[",astree->symbol->text);
					astreeDecompile(astree->son[1],ASTREE_VETOR_DECLARADO_1);
					fprintf(fileout,"] ");
					break;
				
				case ASTREE_VETOR_DECLARADO_2:				
					astreeDecompile(astree->son[0],ASTREE_VETOR_DECLARADO_2);
					fprintf(fileout," %s[",astree->symbol->text);
					astreeDecompile(astree->son[1],ASTREE_VETOR_DECLARADO_2);
					fprintf(fileout,"]: ");
					astreeDecompile(astree->son[2],ASTREE_VETOR_DECLARADO_2);
					break;
	
				case ASTREE_VETOR_CONTEUDO:
					astreeDecompile(astree->son[0],ASTREE_VETOR_CONTEUDO);
					astreeDecompile(astree->son[1],ASTREE_VETOR_CONTEUDO);		
					break;			

				case ASTREE_DECLARACAO_FUNCAO:				
					astreeDecompile(astree->son[0],ASTREE_DECLARACAO_FUNCAO); // imprime o "tipo"
					fprintf(fileout," %s", astree->symbol->text); // imprime o "nome"				
					fprintf(fileout," (");
					astreeDecompile(astree->son[1],ASTREE_DECLARACAO_FUNCAO);
					fprintf(fileout,")");
					astreeDecompile(astree->son[2],ASTREE_DECLARACAO_FUNCAO);
					break;
					
				case ASTREE_PARAMETROS:				
					astreeDecompile(astree->son[0],ASTREE_PARAMETROS); // imprime o "tipo"
					if(astree->symbol)					
					fprintf(fileout," %s", astree->symbol->text); // imprime o "nome"				
					astreeDecompile(astree->son[1],ASTREE_PARAMETROS);
					break;	
			
				case ASTREE_PARAMETROS_RESTO:	
					fprintf(fileout,","); 	
					astreeDecompile(astree->son[0],ASTREE_PARAMETROS); // imprime o "tipo"		
					if(astree->symbol)
					fprintf(fileout," %s", astree->symbol->text); // imprime o "nome"				
					astreeDecompile(astree->son[1],ASTREE_PARAMETROS_RESTO);
					break;	
						
				case ASTREE_BLOCO:
					fprintf(fileout,"\n{\n");
					astreeDecompile(astree->son[0], ASTREE_BLOCO);
					fprintf(fileout,"\n}\n");
					break;

				case ASTREE_VAZIO:
					astreeDecompile(astree->son[0], ASTREE_VAZIO);
					break;

				case ASTREE_INT:
					fprintf(fileout,"int");
					break;

				case ASTREE_FLOAT:
					fprintf(fileout,"float");
					break;	

				case ASTREE_CHAR:
					fprintf(fileout,"char");
					break;

				case ASTREE_BOOL:
					fprintf(fileout,"bool");
					break;

				case ASTREE_SYMBOL:
					fprintf(fileout,"%s",astree->symbol->text);
					break;
					
						
				//------ Comandos ------//
				case ASTREE_LISTA_COMANDOS:
					astreeDecompile(astree->son[0],ASTREE_LISTA_COMANDOS);
					astreeDecompile(astree->son[1],ASTREE_LISTA_COMANDOS);
					fprintf(fileout,";\n");
					break;

				case ASTREE_CMD_ATRIBUICAO:
					fprintf(fileout,"%s",astree->symbol->text);
					fprintf(fileout,"=");
					astreeDecompile(astree->son[0],ASTREE_CMD_ATRIBUICAO);
					break;
				
				case ASTREE_CMD_ATRIBUICAO_VETOR:
					fprintf(fileout,"%s",astree->symbol->text);					
					fprintf(fileout,"[");
					astreeDecompile(astree->son[0],ASTREE_CMD_ATRIBUICAO_VETOR);
					fprintf(fileout,"] = ");
					astreeDecompile(astree->son[1],ASTREE_CMD_ATRIBUICAO_VETOR);
					break;	
					
				case ASTREE_CMD_PRINT:
					if(node_father!=ASTREE_CMD_PRINT)							
						fprintf(fileout, "print ");
					if(astree->symbol)
						fprintf(fileout, "%s ",astree->symbol->text);		
					astreeDecompile(astree->son[0],ASTREE_CMD_PRINT);
					
					if(astree->son[1]!=0) {
						fprintf(fileout, " ");	
						astreeDecompile(astree->son[1],ASTREE_CMD_PRINT);
					}
					break;
					
				case ASTREE_CMD_READ:	
					if(node_father!=ASTREE_CMD_READ)							
						fprintf(fileout, "read ");
					fprintf(fileout,"%s",astree->symbol->text);
					break;		
					
				case ASTREE_CMD_RETURN:					
					fprintf(fileout, "return ");
					astreeDecompile(astree->son[0],ASTREE_CMD_RETURN);
					break;	

				case ASTREE_CHAMADA_FUNCAO:
					fprintf(fileout,"%s",astree->symbol->text);
					fprintf(fileout, "(");
					astreeDecompile(astree->son[0],ASTREE_CHAMADA_FUNCAO);
					fprintf(fileout, ")");
					break;

				case ASTREE_ARGUMENTOS:
					astreeDecompile(astree->son[0],ASTREE_ARGUMENTOS);
					astreeDecompile(astree->son[1],ASTREE_ARGUMENTOS);	
					break;
	
				case ASTREE_RESTO_ARGUMENTOS:	
					fprintf(fileout, ",");	
					astreeDecompile(astree->son[0],ASTREE_RESTO_ARGUMENTOS);
					astreeDecompile(astree->son[1],ASTREE_RESTO_ARGUMENTOS);
					break;		
						
			
				//----- Comandos  de  Controlde  de Fluxo ------//
				case ASTREE_CMD_IF:
					fprintf(fileout, "if (");
					astreeDecompile(astree->son[0],ASTREE_CMD_IF);
					fprintf(fileout, ") then ");
					astreeDecompile(astree->son[1],ASTREE_CMD_IF);
					if(astree->son[2]) 
						astreeDecompile(astree->son[2],ASTREE_CMD_IF);
					break;
				
				case ASTREE_CMD_IF_ELSE:
					fprintf(fileout, "if (");
					astreeDecompile(astree->son[0],ASTREE_CMD_IF_ELSE);
					fprintf(fileout, ") then ");
					astreeDecompile(astree->son[1],ASTREE_CMD_IF_ELSE);
					fprintf(fileout, " else ");
					astreeDecompile(astree->son[2],ASTREE_CMD_IF_ELSE);;
					break;
				
				case ASTREE_CMD_FOR:
					fprintf(fileout, "for(");
					astreeDecompile(astree->son[0],ASTREE_CMD_FOR);
					fprintf(fileout, ") ");
					astreeDecompile(astree->son[1],ASTREE_CMD_FOR);
					break;
					
				case ASTREE_CMD_FOR_TO:
					fprintf(fileout, "for(%s", astree->symbol->text);
					fprintf(fileout, " = ");
					astreeDecompile(astree->son[0],ASTREE_CMD_FOR_TO);
					fprintf(fileout, " to ");
					astreeDecompile(astree->son[1],ASTREE_CMD_FOR_TO);
					fprintf(fileout, ") ");
					astreeDecompile(astree->son[2],ASTREE_CMD_FOR_TO);
					break;	
					
				//----- Expressões Aritméticas e Lógicas -----//
				case ASTREE_ADD:
					astreeDecompile(astree->son[0],ASTREE_ADD);
					fprintf(fileout," + ");
					astreeDecompile(astree->son[1],ASTREE_ADD);
					break;
				
				case ASTREE_SUB:
					astreeDecompile(astree->son[0],ASTREE_SUB);
					fprintf(fileout," - ");
					astreeDecompile(astree->son[1],ASTREE_SUB);
					break;
					
				case ASTREE_MUL:
					astreeDecompile(astree->son[0],ASTREE_MUL);
					fprintf(fileout," * ");
					astreeDecompile(astree->son[1],ASTREE_MUL);
					break;
					
				case ASTREE_DIV:
					astreeDecompile(astree->son[0],ASTREE_DIV);
					fprintf(fileout," / ");
					astreeDecompile(astree->son[1],ASTREE_DIV);
					break;
					
				case ASTREE_MAIOR:
					astreeDecompile(astree->son[0],ASTREE_MAIOR);
					fprintf(fileout," > ");
					astreeDecompile(astree->son[1],ASTREE_MAIOR);
					break;
					
				case ASTREE_MENOR:
					astreeDecompile(astree->son[0],ASTREE_MENOR);
					fprintf(fileout," < ");
					astreeDecompile(astree->son[1],ASTREE_MENOR);
					break;				
					
				case ASTREE_LE:
					astreeDecompile(astree->son[0],ASTREE_LE);
					fprintf(fileout," <= ");
					astreeDecompile(astree->son[1],ASTREE_LE);
					break;
					
				case ASTREE_GE:
					astreeDecompile(astree->son[0],ASTREE_GE);
					fprintf(fileout," >= ");
					astreeDecompile(astree->son[1],ASTREE_GE);
					break;
					
				case ASTREE_EQ:
					astreeDecompile(astree->son[0],ASTREE_EQ);
					fprintf(fileout," == ");
					astreeDecompile(astree->son[1],ASTREE_EQ);
					break;
					
				case ASTREE_NE:
					astreeDecompile(astree->son[0],ASTREE_NE);
					fprintf(fileout," != ");
					astreeDecompile(astree->son[1],ASTREE_NE);
					break;
					
				case ASTREE_AND:
					astreeDecompile(astree->son[0],ASTREE_AND);
					fprintf(fileout," && ");
					astreeDecompile(astree->son[1],ASTREE_AND);
					break;
					
				case ASTREE_OR:
					astreeDecompile(astree->son[0],ASTREE_OR);
					fprintf(fileout," || ");
					astreeDecompile(astree->son[1],ASTREE_OR);
					break;
				
				case ASTREE_NEGACAO:
					fprintf(fileout," !");
					astreeDecompile(astree->son[0],ASTREE_NEGACAO);
					break;		
				
				case ASTREE_EXP_PARENTESES:
					fprintf(fileout,"(");
					astreeDecompile(astree->son[0],ASTREE_EXP_PARENTESES);
					fprintf(fileout,")");
					break;										
					
			}
	}


}


