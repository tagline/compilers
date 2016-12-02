//--------------------------------------------//
// ALUNOS: TAGLINE TREICHEL e BRUNO FILLMANN
//--------------------------------------------//

#include "hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "y.tab.h"

HASH_NODE* Table[HASH_SIZE];


int initHash ()
{
	int i;
	for(i=0;i<HASH_SIZE;i++)
	{
		Table[i] = NULL;
	}

}

int hashAddress(char *text)
{ 
	int i=0;
	int address = 1;

	for(i=0; i<strlen(text);i++)
		address = (address = text[i]%HASH_SIZE+1);
	return address - 1;
}

HASH_NODE *HashFind (char *text)
{
	int address = hashAddress(text);
	HASH_NODE *node;

	for (node=Table[address]; node; node=node->next){
		if ((strcmp(node->text, text)==0)){
			return node;
		}
	}

	return 0;
}

HASH_NODE *hashInsert(int type, char* text)
{
	int address;

	HASH_NODE *existing= malloc(sizeof(HASH_NODE));
	existing =  HashFind(text);

	if (type == TK_IDENTIFIER)
	{
		if (existing)
		{
			return existing;
		}
	}


	HASH_NODE *testnode;
	HASH_NODE *newnode= malloc(sizeof(HASH_NODE));

	address = hashAddress(text);
	newnode->line = getLineNumber();
	newnode->type = type;
	newnode->nature = 0;
	newnode->data_type = 0;
	newnode->declared = 0;
	newnode->parameters = NULL;
	newnode->text = (char*) calloc(strlen(text)+1,sizeof(char));
	strcpy(newnode->text,text);
	newnode->next = NULL;

	if (Table[address] != NULL)
	{
		testnode = Table[address];
		if (testnode -> next ==NULL){
			testnode->next = newnode;
			return newnode;
		}
		else
		{
			while (testnode->next != NULL)
				testnode = testnode->next;
			testnode->next = newnode;
			return newnode;
		}	
	}
	Table[address] = newnode;

	return newnode;
}



void hashPrint(void)
{
	HASH_NODE *node;
	int i=0;

	printf("\n ############ HASH TABLE ##########\n");

	for(i=0;i<HASH_SIZE;i++){
		/*
		for(node = Table[i]; node; node=node->next)
			printf("Table[%d] has %s \n",i,node->text);
		*/
		if (Table[i])
		{
			node = Table[i]; 
			printf("Table[%d] has %s \n",i,node->text);

			while(node->next != NULL)
			{
				node = node->next;
				printf("Table[%d] has %s \n",i,node->text);
			}
		}
		
	}

	printf("##################################\n");

}

HASH_NODE* makeTemp(void)
{
	static char buffer[256];
	static int nextTemp=0;
	sprintf(buffer,"__TeMp%d",nextTemp++);
	return hashInsert(HASH_SCALAR, buffer);
}

HASH_NODE* makeLabel(void)
{
	static char buffer[256];
	static int nextTemp=0;
	sprintf(buffer,"__LaBeL%d",nextTemp++);
	return hashInsert(HASH_LABEL, buffer); 
}

void saveASM(FILE *fout) 
{
	int i=0;
	HASH_NODE * node;

	fprintf(fout, "\t.data\n");

	for(i=0;i<HASH_SIZE;i++)
		for(node=Table[i]; node; node=node->next)
			if(node->type != HASH_FUNCTION && node->type != HASH_LABEL)
			{	
			if(node->type == HASH_SCALAR || node->type == HASH_VECTOR)
				fprintf(fout, "_%s:\t.long 0\n", node->text);
			else
				fprintf(fout, "_%s:\t.long %s\n", node->text, node->text);					
			}

	fprintf(fout, "\t.cstring\n"
	"LC0:.ascii \"%%d\\0\n "
	"\t.text\n");
	
}



