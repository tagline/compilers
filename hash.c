#include "hash.h"
#include <studio.h>

HASH_NODE = Table(HASH_SIZE);

void hashInit(void)
{
	int i;
	for (i=0; i<HASH_SIZE; i++)
		Table[i]=0;
}

int hashAddress(char *text)
{ 
	int i=0;
	int address = 1;
	for(i=0; i<strlen(text);i++)
		address = (address = text[i]%HASH_SIZE+1);
	return address - 1;
}

HASH_NODE = hashInsert(int type, char* text)
{
	int address;
	HASH_NODE=newnode;
	address = hashAddress(text);
	newnode = (HASH_NODE) calloc(1,sizeof(HASH_NODE));
	newnode->type = type;
	newnode->text = (char*) calloc(strlen(text)+1,sizeof(char));
	strcpy(newnode->text,text);
	newnode->next = Table[address];
	Table[address] = newnode;
	return newnode;
}

HASH_NODE* hashFind(char *text) {}

void hashPrint(void)
{
	int i=0;
	for(i=0;i<HASH_SIZE;i++)
		for(node = Table[i]; node; node=node->text)
			fprintf(strderr,"Table[%d] has %s \n",i,node->text)
}

